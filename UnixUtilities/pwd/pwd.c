#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    char *CurrPath = NULL;
    /*
        pass nullpointer  and size = 0 to delegate allocating memory to getcwd
        it will allocate a big enough buffer for the path
        user should free it
    */
    CurrPath = getcwd(NULL, 0);
    if (NULL == CurrPath)
    {
        printf("ERROR, Can't get current path , errno=%dn", errno);
        return -2;
    }
    else
    {
        printf("%s\n", CurrPath);
        free(CurrPath);
        CurrPath = NULL;
    }

    return 0;
}
