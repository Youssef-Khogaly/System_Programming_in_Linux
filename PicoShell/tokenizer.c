#include <tokenizer.h>

void Tokenizer_init(Commands_t *Command)
{
    Command->argc = 0;
    Command->argv = (char **)calloc(INIT_ARGV_CAPACITY, sizeof(char *));
    Command->argvCapacity = INIT_ARGV_CAPACITY;
}

/*
 @details free  argv[0] till argv[argc-1] and set them to NULL;
          and set argc to 0
*/
void Tokenizer_free_ArgvStrs(Commands_t *command)
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

/**
 *
 * totally free all Commands_t pointers and set them to null
 * if they aren't freed
 * and set argc & argvCapacity to 0
 */
void Tokenizer_free_all(Commands_t *comm)
{
    if (comm)
    {
        Tokenizer_free_ArgvStrs(comm);
        if (comm->argv)
        {
            free(comm->argv);
            comm->argv = NULL;
            comm->argvCapacity = 0;
        }
    }
}
int Tokenize_Line(char *Line, int size, Commands_t *out)
{
    if (!Line || !out || size == 0)
    {
        return -1;
    }
    else if (size == 0)
        return -3;

    char *str = Line;
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
            if (out->argc == (out->argvCapacity))
            {
                ++(out->argvCapacity);
                out->argv = (char **)realloc(out->argv, out->argvCapacity * sizeof(char *));
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
    if (out->argc == out->argvCapacity)
    {
        ++(out->argvCapacity);
        out->argv = (char **)realloc(out->argv, out->argvCapacity * sizeof(char *));
    }
    out->argv[out->argc] = ((char *)NULL);
    free(temp);
    return 0;
}