#include "cat.h"

#define BUFFER_SIZE (256U)

enum
{
    READ_FAIL = -3,
    BAD_USAGE = -2,
    OPEN_FAIL = -1,
    SUCCESS
} errors_t;

int cat(int argc, char *argv[])
{
    uint8_t buffer[BUFFER_SIZE] = {0};
    ssize_t ret = EXIT_SUCCESS;
    if (argc != 2)
    {
        fprintf(stderr, "Bad Usage, cat [file path]\n");
        ret = BAD_USAGE;
    }
    else
    {
        char *ReadPath = argv[1];
        int fd = open(ReadPath, O_RDONLY);
        if (fd == -1)
        {
            printf("Can't open the file , path = %s\n", argv[1]);
            ret = OPEN_FAIL;
        }
        else
        {
            int NumOfReaded = 0;
            while ((NumOfReaded = read(fd, buffer, BUFFER_SIZE)) > 0)
            {
                if (-1 == write(STDOUT_FILENO, buffer, NumOfReaded))
                {
                    printf("Write Failed\n");
                    break;
                }
            }
            if (NumOfReaded == -1)
            {
                printf("Error while Reading file , path: %s\n", ReadPath);
                ret = READ_FAIL;
            }
            else
                ret = SUCCESS;

            close(fd);
        }
    }
    return 0;
}
