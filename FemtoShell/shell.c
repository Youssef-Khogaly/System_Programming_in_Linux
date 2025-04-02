#include <shell.h>

int main()
{
    char *input = (char *)calloc(INPUT_BUFFER_INIT_SIZE, sizeof(char));
    size_t inputSize = INPUT_BUFFER_INIT_SIZE;
    ssize_t ReadedInputSize = 0;
    Commands_t command;
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
                    break; // exit command
                }
            }

            Tokenizer_free_ArgvStrs(&command);
        }
    }
    free(input);
    Tokenizer_free_all(&command);
    return EXIT_SUCCESS;
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
