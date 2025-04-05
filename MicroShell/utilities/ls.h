#ifndef _LS_H_
#define _LS_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdbool.h>


int ls(int argc, char *argv[]);
#endif