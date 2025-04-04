#include <shell.h>

extern char **environ;
list_t *LocalVariablesList = NULL;
/*
    0 -> true
    1 -> not a localVarCommand
    -1 -> wrong format local var command
*/

int main()
{
    char *input = (char *)calloc(INPUT_BUFFER_INIT_SIZE, sizeof(char));
    size_t inputSize = INPUT_BUFFER_INIT_SIZE;
    LocalVariablesList = list_create();
    ssize_t ReadedInputSize = 0;
    Commands_t command;
    setenv("PATH", _ENV_PATH_, 1);
    Tokenizer_init(&command);
    while (1)
    {
        printf("Shell:");
        ReadedInputSize = getline(&input, &inputSize, stdin);
        if (ReadedInputSize == (ssize_t)(-1) && errno == 0) // end of file reached
        {
            break;
        }
        else if (ReadedInputSize == (ssize_t)(-1) && errno != 0) // error while reading
        {
            fprintf(stderr, "err:getline failled reading line! ,errno = %d\n", errno);
            free(input);
            input = NULL;
            Tokenizer_free_all(&command);
            exit(-1);
        }
        else if (ReadedInputSize == 1) // new line only
            continue;
        else
        {
            input[ReadedInputSize - 1] = 0; // remove the readed \n from the buffer
            --ReadedInputSize;
            int ret = Tokenize_Line(input, ReadedInputSize, &command);
            if (ret == -2)
            {
                fprintf(stderr, "Memory allocation failure too large command , file = %s , line = %d\n", __FILE__, __LINE__);
            }
            else
            {
                if (1 == ExecuteCommand(&command))
                {
                    printf("Good bye");
                    break; // exit command
                }
            }

            Tokenizer_free_ArgvStrs(&command);
        }
    }
    free(input);
    Tokenizer_free_all(&command);
    list_clear(&LocalVariablesList);
    free(LocalVariablesList);
    return EXIT_SUCCESS;
}

/**
 *
 * return :
 *           0 success
 *           1 exit
 */
int ExecuteCommand(Commands_t *command)
{
    pid_t childPid;
    int wStat;
    if (LocalVariableAssignHandler(command))
        return 0;

    LocalVariableReplace(command);
    if (command->argc == 0)
    {
        return 0;
    }
    else if (strncmp("exit", command->argv[0], 4) == 0)
        return 1;
    else if (strncmp("cd", command->argv[0], 2) == 0)
    {
        cdCommand(command->argc, command->argv);
        return 0;
    }
    else if (strncmp("export", command->argv[0], 6) == 0)
    {
        export(command);
        return 0;
    }

    else if (strncmp("printenv", command->argv[0], 8) == 0)
    {
        printEnv();
        return 0;
    }
    // duplicate current process
    childPid = fork();

    /*Parent*/
    if (childPid > 0)
    {
        pid_t ret = waitpid(childPid, &wStat, 0);
        if (-1 == ret)
        {
            fprintf(stderr, "waiting child termination fail , errno = %d\n", errno);
        }
    }
    else if (childPid == -1) /*Parent , creating child process failed*/
    {
        fprintf(stderr, "Error can't create child process , errno = %d\n", errno);
    }
    /* Child*/
    else
    {
        execvp(command->argv[0], command->argv);
        if (errno == ENOENT)
        {
            fprintf(stderr, "%s: no such file or command\n", command->argv[0]);
        }
        else if (errno == EACCES)
        {
            fprintf(stderr, "%s:Access denied\n", command->argv[0]);
        }
        else
        {
            fprintf(stderr, "error returning from execvp , bin:%s , errno =%d\n", command->argv[0], errno);
        }

        exit(errno);
    }
    return 0;
}

void cdCommand(int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf(stderr, "cd: too many argument\n");
        return;
    }
    else if (argc == 1)
        return;

    int ret = chdir(argv[1]);

    if (ret == -1)
    {
        switch (errno)
        {
        case EACCES:
            fprintf(stderr, "permission is denied\n");
            break;
        case ENONET:
            fprintf(stderr, "The directory specified in path does not exist\n");
            break;
        case ENOTDIR:
            fprintf(stderr, "Not a directory\n");
            break;
        default:
            fprintf(stderr, "Error , errno = %d", errno);
            break;
        }
    }
}

bool LocalVariableAssignHandler(Commands_t *comm)
{
    if (comm->argc != 1)
        return false;
    int i = 0;
    for (i = 0; i < comm->argc; ++i)
    {
        char *commCpy = strchr(comm->argv[i], '=');
        if (commCpy == NULL)
        {
            return false;
        }
        else
        {
            commCpy = strdup(comm->argv[i]);
        }
        char *key = strtok(commCpy, "=");
        char *value = strtok(NULL, "=");
        list_Append(&LocalVariablesList, key, value);
    }
    return true;
}
void LocalVariableReplace(Commands_t *comm)
{
    if (comm == NULL)
        return;
    int i = 0;
    char *tempBuffer = NULL;
    for (i = 0; i < comm->argc; ++i)
    {
        char *DollarSignLocation = strchr(comm->argv[i], '$');
        if (NULL != DollarSignLocation)
        {
            char *val = list_GetVal(LocalVariablesList, DollarSignLocation + 1);
            if (val != NULL)
            {
                // change dolar sign location to null too seprate key name and chars before dollar sign
                // to handle case /$x
                DollarSignLocation[0] = 0;
                // len of string before $
                size_t argvLenBeforeSign = strlen(comm->argv[i]);
                // len of val
                size_t valLen = strlen(val);
                tempBuffer = (char *)malloc(argvLenBeforeSign + valLen + 1);
                if (argvLenBeforeSign == 0)
                {
                    strcpy(tempBuffer, val);
                }
                else
                {
                    strcpy(tempBuffer, comm->argv[i]);
                    strcat(tempBuffer, val);
                }
                free(comm->argv[i]);
                comm->argv[i] = tempBuffer;
            }
            else // non existing var
            {
                free(comm->argv[i]);
                comm->argv[i] = strdup("");
            }
        }
    }
}

void printEnv()
{
    for (int i = 0; NULL != environ[i]; ++i)
        printf("%s\n", environ[i]);
}
void export(Commands_t *comm)
{
    if (comm == NULL)
    {
        return;
    }
    else if (comm->argc != 2)
    {
        fprintf(stderr, "invalid number of argument for export\n");
        return;
    }
    char *key = comm->argv[1];
    char *val = list_GetVal(LocalVariablesList, key);
    char *temp = (char *)malloc(strlen(key) + strlen(val) + 2);
    char *end = stpcpy(temp, key); // return pointer to the null terminator
    // add equal sign
    end[0] = '=';
    end[1] = '\0';
    strcat(temp, val);
    int ret = putenv(temp);
    if (ret != 0)
    {
        fprintf(stderr, "Err.Can't add %s to env variables , errno = %d\n", key, errno);
    }
}