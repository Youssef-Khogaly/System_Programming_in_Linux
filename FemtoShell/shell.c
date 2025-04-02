#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <echo.h>
#include <errno.h>
#define INIT_ARGV_CAP (4)
#define INPUT_BUFFER_INIT_SIZE (256U)
typedef struct
{
    int argc;
    char **argv;
    int argvcapacity;
} Commands_t;
void free_commandBuffers(Commands_t *command)
{
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
void free_commandCap(Commands_t *comm)
{
    if (comm)
    {
        if (comm->argv)
        {
            free(comm->argv);
            comm->argv = NULL;
            comm->argvcapacity = 0;
        }
    }
}
/**
 *
 * parse input line to argc and argv
 */
int InputParser(char *input, int size, Commands_t *out);

/*
 * validate command and execute it
 */
int ExecuteCommand(const Commands_t *command);
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
            free_commandBuffers(&command);
            free_commandCap(&command);
            exit(-1);
        }
        else if (ReadedInputSize == 1) // new line only
            continue;
        else
        {
            int ret = InputParser(input, ReadedInputSize, &command);
            if (ret == -2)
            {
                fprintf(stderr, "Memory allocation faill , file = %s , line = %d\n", __FILE__, __LINE__);
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
    free_commandBuffers(&command);
    free_commandCap(&command);
    return EXIT_SUCCESS;
}

/*
    return:
            0 - > success
            -1 -> Null ptr
            -2 -> no enough memory
*/
int InputParser(char *input, int size, Commands_t *out)
{
    if (!input || !out)
    {
        printf("null pointer passed to input Parser \n");
        return -1;
    }

    char *str = input;
    char *temp = (char *)malloc(size + 1);
    int tempLen = 0;
    int i = 0;
    if (temp == NULL)
    {
        return -2;
    }

    // Skip leading spaces
    while (i < size && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
        i++;

    while (i < size)
    {
        // Reset tempLen for each new token
        tempLen = 0;

        // Copy characters into temp until a space or newline is encountered
        while (i < size && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            temp[tempLen++] = str[i++];
        }

        // Only store non-empty tokens
        if (tempLen > 0)
        {
            temp[tempLen++] = '\0'; // Null terminate the string , ++ to include null terminator in tempLen
            // handling large number of argument
            if (out->argc == (out->argvcapacity - 1))
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
            strncpy(out->argv[out->argc], temp, tempLen + 1);
            ++(out->argc);
        }

        // Skip consecutive spaces/tabs/newlines
        while (i < size && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            i++;
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