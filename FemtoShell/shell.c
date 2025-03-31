#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <echo.h>

#define INPUT_BUFFER_SIZE (256U)
#define INIT_ARGV_CAP (32)

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
void InputParser(char *input, int size, Commands_t *out);

/*
* validate command and execute it 
*/
int ExecuteCommand(const Commands_t *command);
int main()
{
    char input[INPUT_BUFFER_SIZE] = {0};
    Commands_t command = {.argc = 0, .argv = (char **)calloc(INIT_ARGV_CAP, sizeof(char *)), .argvcapacity = INIT_ARGV_CAP};
    while (1)
    {
        printf("Shell:");
        fgets(input, INPUT_BUFFER_SIZE, stdin);
        InputParser(input, strlen(input), &command);

        if (1 == ExecuteCommand(&command))
        {
            break;
        }
        free_commandBuffers(&command);
    }
    free_commandBuffers(&command);
    free_commandCap(&command);
    return EXIT_SUCCESS;
}

void InputParser(char *input, int size, Commands_t *out)
{
    if (!input || !out)
    {
        printf("null pointer passed to input \n");
        return;
    }
    char *str = input;
    char temp[32] = {0};
    int tempLen = 0;
    int i = 0;
    while (i < size)
    {

        for (tempLen = 0; i < size; ++i)
        {

            if (str[i] != ' ' && str[i] != '\n') // skip space and \n
                temp[tempLen++] = str[i];
            else if (tempLen != 0) // break at first space after command
                break;
        }

        if (i >= size && tempLen == 0)
            break;
        if (out->argc == (out->argvcapacity - 1))
        {
            ++(out->argvcapacity);
            out->argv = (char **)realloc(out->argv, out->argvcapacity * sizeof(char *));
        }
        out->argv[out->argc] = (char *)malloc(tempLen * sizeof(char));
        temp[tempLen++] = '\0'; // add nullterminator
        strncpy(out->argv[out->argc], temp, tempLen);
        ++(out->argc);
    }
}

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