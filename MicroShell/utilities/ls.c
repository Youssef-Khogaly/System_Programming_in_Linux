#include "ls.h"
#define DIR_COLOUR "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

void ListDirFiles(char *Path)
{
    DIR *ListDir = opendir(Path);
    if (NULL == ListDir)
    {
        switch (errno)
        {
        case 0:
            break;
        case EACCES:
            fprintf(stderr, "Permission denied , accessing %s\n", Path);
            return;
        case ENONET:
            fprintf(stderr, "Directory does not exist, path %s\n", Path);
            return;
        case ENOTDIR:
            fprintf(stderr, "%s is not a directory\n", Path);
            return;
        default:
            fprintf(stderr, "error while opening the dir %s , errno = %d", Path, errno);
            return;
        }
    }
    struct dirent *dir = NULL;
    while ((dir = readdir(ListDir)) != NULL)
    {
        printf("%s  ", dir->d_name);
    }
    if (errno != 0)
    {
        fprintf(stderr, "error while readding dir,errno = %d\n", errno);
    }
}

int ls(int argc, char *argv[])
{

    bool multiFiles = (argc > 2);

    int i = 1;
    if (argc == 1)
    {
        ListDirFiles(".");
        printf("\n");
    }
    else
    {
        while (i < argc)
        {

            if (multiFiles)
                printf("%s:\n", argv[i]);

            ListDirFiles(argv[i]);
            printf("\n");

            ++i;
        }
    }

    return 0;
}
