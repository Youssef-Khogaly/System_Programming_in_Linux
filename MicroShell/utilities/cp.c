
#include "cp.h"

#define BUFFER_SIZE (512U)

int cp(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Bad usage: cp [source] [desniation]\n");
        return -1;
    }
    uint8_t buffer[BUFFER_SIZE] = {0};
    ssize_t NumOfReaded = 0;
    int src_fd = -1;
    int dest_fd = 1;
    char *src = argv[1];
    char *dest = argv[2];

    /* opening source and dest files*/
    if ((src_fd = open(src, O_RDONLY)) == -1)
    {
        fprintf(stderr, "error opening the file , path: %s\n", src);
        return errno;
    }
    if ((dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 400)) == -1)
    {
        fprintf(stderr, "error opening the file , path: %s\n", dest);
        close(src_fd);
        return errno;
    }

    while ((NumOfReaded = read(src_fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (-1 == write(dest_fd, buffer, NumOfReaded))
        {
            fprintf(stderr, "error while writing to dest file , path: %s\n", src);
            close(src_fd);
            close(dest_fd);
            return errno;
        }
    }
    close(src_fd);
    close(dest_fd);

    if (NumOfReaded == -1)
    {
        fprintf(stderr, "error while reading the src file , path: %s\n", src);
        return errno;
    }

    return 0;
}