#include <shell.h>

#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

extern char **environ;

list_t *LocalVariablesList = NULL;

static int SavedStdinFD;
static int SavedStdoutFD;
static int SavedStderrFD;

static int executeBuiltIn(Commands_t *command);

static void executeBinary(Commands_t *command);
int main()
{
    char *input = (char *)calloc(INPUT_BUFFER_INIT_SIZE, sizeof(char));
    size_t inputSize = INPUT_BUFFER_INIT_SIZE;
    LocalVariablesList = list_create();
    ssize_t ReadedInputSize = 0;
    Commands_t command;
    Tokenizer_init(&command);
    char *currentDir = NULL;
    SavedStdinFD = dup(STDIN_FILENO);
    SavedStdoutFD = dup(STDOUT_FILENO);
    SavedStderrFD = dup(STDERR_FILENO);
    char hostName[64];
    gethostname(hostName, 64);
    while (1)
    {
        currentDir = get_current_dir_name();
        printf(ANSI_COLOR_GREEN "%s@%s" ANSI_COLOR_RESET ":", getlogin(), hostName);
        printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "$", currentDir);
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
        free(currentDir);
    }
    free(input);
    free(currentDir);
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

    if (LocalVariableAssignHandler(command))
        return 0;

    LocalVariableReplace(command);
    if (command->argc == 0)
    {
        return 0;
    }
    int redirectionFlag = IO_RedirectionHandler(command);
    if (redirectionFlag == -1)
        return 0;
    int ret = executeBuiltIn(command);
    // redirect stdin and stdout and stderr back
    if (redirectionFlag != 0)
    {
        // redirect stdin to standard
        if (redirectionFlag & STDIN_REDIRECTED_MASK)
        {
            dup2(SavedStdinFD, STDIN_FILENO);
        }
        // redirect stdout to standard
        if (redirectionFlag & STDOUT_REDIRECTED_MASK)
        {
            if (dup2(SavedStdoutFD, STDOUT_FILENO) < 0)
                fprintf(stderr, "dup2 , errno = %d\n", errno);
        }
        // redirect stderr to standard
        if (redirectionFlag & STDERR_REDIRECTED_MASK)
        {
            dup2(SavedStderrFD, STDERR_FILENO);
        }
        return ret;
    }
    if (ret == 0 || ret == 1) // built in command executed return
        return ret;

    // not build in command , try to execute binary
    executeBinary(command);
    // redirect stdin and stdout and stderr back
    if (redirectionFlag != 0)
    {
        // redirect stdin to standard
        if (redirectionFlag & STDIN_REDIRECTED_MASK)
        {
            dup2(SavedStdinFD, STDIN_FILENO);
        }
        // redirect stdout to standard
        if (redirectionFlag & STDOUT_REDIRECTED_MASK)
        {
            if (dup2(SavedStdoutFD, STDOUT_FILENO) != 0)
                fprintf(stderr, "dup2 , errno = %d\n", errno);
        }
        // redirect stderr to standard
        if (redirectionFlag & STDERR_REDIRECTED_MASK)
        {
            dup2(SavedStderrFD, STDERR_FILENO);
        }
    }
    return 0;
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
    char *temp = strchr(comm->argv[1], '=');
    if (NULL != temp)
    {
        int ret = putenv(strdup(comm->argv[1]));
        if (ret != 0)
        {
            fprintf(stderr, "Err.Can't add variable to env variables , errno = %d\n", errno);
        }
    }
    else
    {
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
}

static int executeBuiltIn(Commands_t *command)
{
    if (strncmp("exit", command->argv[0], 4) == 0)
        return 1;
    else if (strncmp("cd", command->argv[0], 2) == 0)
    {
        cd(command->argc, command->argv);
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
    else if (strncmp("ls", command->argv[0], 2) == 0)
    {
        ls(command->argc, command->argv);
        return 0;
    }
    else if (strncmp("pwd", command->argv[0], 3) == 0)
    {
        pwd();
        return 0;
    }
    else if (strncmp("cp", command->argv[0], 2) == 0)
    {
        cp(command->argc, command->argv);
        return 0;
    }
    else if (strncmp("mv", command->argv[0], 2) == 0)
    {
        mv(command->argc, command->argv);
        return 0;
    }
    else if (strncmp("echo", command->argv[0], 4) == 0)
    {
        echo(command->argc, command->argv);
        return 0;
    }
    else if (strncmp("cat", command->argv[0], 3) == 0)
    {
        cat(command->argc, command->argv);
        return 0;
    }
    else if (strcmp("unsetenv", command->argv[0]) == 0)
    {
        if (command->argc == 2)
        {
            if (0 != unsetenv(command->argv[1]))
            {
                fprintf(stderr, "error,can't unset enviroment variable , errno =%d\n", errno);
            }
        }
        else if (command->argc > 2)
            fprintf(stderr, "bad usage: unsetenv [env variable name]\n");

        return 0;
    }
    else if (strncmp("unset", command->argv[0], 5) == 0)
    {
        // unset local variables
        if (command->argc == 2)
            list_Delete(&LocalVariablesList, command->argv[1]);
        else if (command->argc > 2)
            fprintf(stderr, "bad usage: unset [local variable name]\n");
        return 0;
    }

    return -1;
}
static void executeBinary(Commands_t *command)
{
    pid_t childPid;
    int wStat;
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
    return;
}

int IO_RedirectionHandler(Commands_t *comm)
{
    int i = 0;
    int newfd;
    int argc_StartOfRedirectingCommand = -1; // store the start of redirecting command argv to delete it all after finish
    int ret = 0;
    for (; i < comm->argc; ++i)
    {
        if (comm->argv[i][0] == '<') // redirect stdin
        {
            if (argc_StartOfRedirectingCommand == -1)
                argc_StartOfRedirectingCommand = i;
            if ((newfd = open(comm->argv[i + 1], O_RDONLY, S_IRWXU)) > 0)
            {
                int duperr = dup2(newfd, STDIN_FILENO);
                close(newfd);
                if (duperr == -1)
                {
                    fprintf(stderr, "error,while redirecting stdin,errno=%d\n", errno);
                    return -1;
                }
                ret |= STDIN_REDIRECTED;
            }
            else
            {
                fprintf(stderr, "err,Can't open %s,errno=%d\n", comm->argv[i + 1], errno);
                return -1;
            }
        }
        else if (comm->argv[i][0] == '>') // redirecting stdout
        {
            if (argc_StartOfRedirectingCommand == -1)
                argc_StartOfRedirectingCommand = i;

            if ((newfd = open(comm->argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) > 0)
            {
                int duperr = dup2(newfd, STDOUT_FILENO);
                close(newfd);
                if (duperr == -1)
                {
                    fprintf(stderr, "error,while redirecting stdout,errno=%d\n", errno);
                    return -1;
                }
                ret |= STDOUT_REDIRECTED;
            }
            else
            {
                fprintf(stderr, "err,Can't open/create %s,errno=%d\n", comm->argv[i + 1], errno);
                return -1;
            }
        }
        else if (strncmp(comm->argv[i], "2>", 2) == 0)
        {
            if (argc_StartOfRedirectingCommand == -1)
                argc_StartOfRedirectingCommand = i;

            if ((newfd = open(comm->argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) > 0)
            {
                int duperr = dup2(newfd, STDERR_FILENO);
                close(newfd);
                if (duperr == -1)
                {
                    fprintf(stderr, "error,while redirecting stderr,errno=%d\n", errno);
                    return -1;
                }
                ret |= STDERR_REDIRECTED;
            }
            else
            {
                fprintf(stderr, "err,Can't open/create %s,errno=%d\n", comm->argv[i + 1], errno);
                return -1;
            }
        }
    }

    if (argc_StartOfRedirectingCommand != -1)
    {
        i = argc_StartOfRedirectingCommand;
        free(comm->argv[i]);
        comm->argc = argc_StartOfRedirectingCommand;
        comm->argv[i] = NULL;
        ++i;
        for (; i < comm->argc; ++i)
        {
            free(comm->argv[i]);
            comm->argv[i] = NULL;
        }
    }
    return ret;
}