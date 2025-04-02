#include <shell.h>

int main()
{
    char *input = (char *)calloc(INPUT_BUFFER_INIT_SIZE, sizeof(char));
    size_t inputSize = INPUT_BUFFER_INIT_SIZE;
    ssize_t ReadedInputSize = 0;
    Commands_t command = {.argc = 0, .argv = (char **)calloc(INIT_ARGV_CAP, sizeof(char *)), .argvcapacity = INIT_ARGV_CAP};
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
            free_command(&command);
            exit(-1);
        }
        else if (ReadedInputSize == 1) // new line only
            continue;
        else
        {
            input[ReadedInputSize - 1] = 0; // remove the readed \n from the buffer
            --ReadedInputSize;
            int ret = InputParser(input, ReadedInputSize, &command);
            if (ret == -2)
            {
                fprintf(stderr, "Memory allocation failure too large command , file = %s , line = %d\n", __FILE__, __LINE__);
            }
            else
            {
                if (1 == ExecuteCommand(&command))
                {
                    break; // exit command
                }
            }

            free_commandBuffers(&command);
        }
    }
    free(input);
    input = NULL;
    free_command(&command);
    return EXIT_SUCCESS;
}

/*
    return:
            0 - > success
            -1 -> input or out are null ptr
            -2 -> memory allocation faill
            -3 -> size = 0
*/
int InputParser(char *input, int size, Commands_t *out)
{
    if (!input || !out || size == 0)
    {
        return -1;
    }
    else if (size == 0)
        return -3;

    char *str = input;
    char *temp = (char *)malloc(size + 1);
    int tempLen = 0;
    int i = 0;
    if (temp == NULL)
    {
        return -2;
    }

    // Skip leading serparator
    while (i < size && IS_SEPARATOR(str[i]))
        i++;

    while (i < size)
    {
        // Reset tempLen for each new token
        tempLen = 0;
        // Skip leading separator
        while (i < size && IS_SEPARATOR(str[i]))
            i++;
        // Copy characters into temp until next separator
        while (i < size && !IS_SEPARATOR(str[i]))
        {
            temp[tempLen++] = str[i++];
        }

        // Only store non-empty tokens
        if (tempLen > 0)
        {
            temp[tempLen++] = '\0'; // Null terminate the string , ++ to include null terminator in tempLen
            // handling large number of argument
            if (out->argc == (out->argvcapacity))
            {
                ++(out->argvcapacity);
                out->argv = (char **)realloc(out->argv, out->argvcapacity * sizeof(char *));
                if (out->argv == NULL)
                {
                    free(temp);
                    return -2;
                }
            }

            out->argv[out->argc] = (char *)malloc((tempLen) * sizeof(char));
            if (out->argv[out->argc] == NULL)
            {
                free(temp);
                return -2;
            }
            strncpy(out->argv[out->argc], temp, tempLen);
            ++(out->argc);
        }
    }
    /*keeping  argv[argc] == NULL to meet C standard*/
    if (out->argc == out->argvcapacity)
    {
        ++(out->argvcapacity);
        out->argv = (char **)realloc(out->argv, out->argvcapacity * sizeof(char *));
    }
    out->argv[out->argc] = NULL;
    free(temp);
    return 0;
}

/**
 *
 * return : 0 success
 *          1 exit
 */
int ExecuteCommand(const Commands_t *command)
{

    if (command->argc == 0)
    {
        printf("\n");
        return 0;
    }
    if (!strcmp(command->argv[0], "echo"))
        return echo(command->argc, command->argv);
    else if (!strcmp(command->argv[0], "exit"))
    {
        printf("Good Bye :)\n");
        return 1;
    }
    else
    {
        printf("%s: command not found\n", command->argv[0]);
    }
    return 0;
}

void free_commandBuffers(Commands_t *command)
{
    if (!command)
        return;
    for (int i = 0; i < command->argc; ++i)
    {
        if (command->argv[i])
        {
            free(command->argv[i]);
            command->argv[i] = NULL;
        }
    }
    command->argc = 0;
}
void free_command(Commands_t *comm)
{
    if (comm)
    {
        free_commandBuffers(comm);
        if (comm->argv)
        {
            free(comm->argv);
            comm->argv = NULL;
            comm->argvcapacity = 0;
        }
    }
}