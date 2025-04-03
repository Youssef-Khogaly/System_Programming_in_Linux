#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdbool.h>

void ListDirFiles(char *Path, uint8_t flag)
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

int main(int argc, char *argv[])
{

    DIR *ListDir = NULL;
    struct dirent *dir = NULL;
    bool multiFiles = (argc > 2);

    int i = 1;
    if (argc == 1)
    {
        ListDirFiles(".", 0);
    }
    else
    {
        while (i < argc)
        {

            if (multiFiles)
                printf("%s:\n", argv[i]);

            ListDirFiles(argv[i], 0);
            if (multiFiles)
                printf("\n");

            ++i;
        }
    }

    return 0;
}
