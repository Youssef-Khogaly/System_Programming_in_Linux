#include "cd.h"
int cd(int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf(stderr, "cd: too many argument\n");
        exit(-1);
    }
    else if (argc == 1)
        return 0;

    if (argv[1][0] == '~')
    {
        const char *homeDir = getenv("HOME");
        if (homeDir)
        {
            size_t homeLen = strlen(homeDir);
            char *temp = (char *)calloc(homeLen + strlen(argv[1]) + 1, sizeof(char));
            char *removed = argv[1] + 1;
            char *last = strncpy(temp, homeDir, homeLen + 1);
            strcat(last, removed);
            free(argv[1]);
            argv[1] = temp;
        }
    }

    int ret = chdir(argv[1]);

    if (ret == -1)
    {
        switch (errno)
        {
        case EACCES:
            fprintf(stderr, "permission is denied\n");
            break;
        case ENOTDIR:
            fprintf(stderr, "Not a directory\n");
            break;
        case ENOENT:
            fprintf(stderr, "No such file or directory\n");
            break;
        default:
            fprintf(stderr, "Error, errno = %d", errno);
            break;
        }
    }

    return 0;
}
