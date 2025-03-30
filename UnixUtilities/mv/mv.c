#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Bad_usage , format: ./mv [src file] [dest file]\n");
        exit(-1);
    }
    char *src = argv[1];
    char *dest = argv[2];
    int ret = rename(src, dest);
    if (ret == -1)
    {
        fprintf(stderr, "Error  while moving [%s] to [%s] !! \n", src, dest);
        exit(errno);
    }

    return 0;
}