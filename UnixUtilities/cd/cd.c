#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf(stderr, "cd: too many argument\n");
        exit(-1);
    }
    else if (argc == 1)
        return 0;

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

    return 0;
}
