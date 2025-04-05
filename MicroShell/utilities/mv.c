#include "mv.h"
int mv(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Bad_usage ,mv [src file] [dest file]\n");
        return -1;
    }
    char *src = argv[1];
    char *dest = argv[2];
    int ret = rename(src, dest);
    if (ret == -1)
    {
        fprintf(stderr, "Error  while moving [%s] to [%s] !! \n", src, dest);
        return errno;
    }

    return 0;
}