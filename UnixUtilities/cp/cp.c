#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define BUFFER_SIZE (512U)

enum
{
    READ_FAIL = -3,
    BAD_USAGE = -2,
    OPEN_FAIL = -1,
    SUCCESS
} errors_t;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Bad usage: should be cp [source] [desniation]\n");
        return BAD_USAGE;
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
        exit(errno);
    }
    if ((dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 400)) == -1)
    {
        fprintf(stderr, "error opening the file , path: %s\n", dest);
        close(src_fd);
        exit(errno);
    }

    while ((NumOfReaded = read(src_fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (-1 == write(dest_fd, buffer, NumOfReaded))
        {
            fprintf(stderr, "error while writing to dest file , path: %s\n", src);
            close(src_fd);
            close(dest_fd);
            exit(errno);
        }
    }
     close(src_fd);
     close(dest_fd);

    if (NumOfReaded == -1)
    {
        fprintf(stderr, "error while reading the src file , path: %s\n", src);
        exit(errno);
    }
    
    return 0;
}
