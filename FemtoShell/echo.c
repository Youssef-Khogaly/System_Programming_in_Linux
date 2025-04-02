#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int echo(int argc, char *argv[])
{
    char space[1] = {' '};
    char newLine[1] = {'\n'};
    if (argc == 1)
    {
        // nothing
    }
    else
    {
        for (int i = 1; i < argc; ++i)
        {
            write(STDOUT_FILENO, argv[i], strlen(argv[i]));
            if (argc - 1 != i)
                write(STDOUT_FILENO, space, 1);
        }
        write(STDOUT_FILENO, newLine, 1);
    }

    return 0;
}