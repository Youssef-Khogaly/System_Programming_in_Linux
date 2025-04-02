
#ifndef _SHELL_H_
#define _SHELL_H_
/*******Includes***********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <echo.h>
#include <errno.h>

/****************defines**************************/
#define INIT_ARGV_CAP (4)
#define INPUT_BUFFER_INIT_SIZE (8)

/*************User Defined types***************/
typedef struct
{
    int argc;
    char **argv;
    int argvcapacity;
} Commands_t;

enum
{
    SPACE = ' ',
    TAB = '\t'
} Separators_t;
/****************Macros**************************/

#define IS_SEPARATOR(_CHAR) (((SPACE == _CHAR) || (TAB == _CHAR)))
/*******************Interfaces******************** */

/*
 @details free  argv[0] till argv[argc-1] and set them to NULL;
          and set argc to 0
*/
void free_commandBuffers(Commands_t *command);

/**
 *
 * totally free all Commands_t pointers and set them to null
 * if they aren't freed
 * and set argc & argvcapacity to 0
 */
void free_command(Commands_t *comm);

/**
 *
 * parse input line to argc and argv
 */
int InputParser(char *input, int size, Commands_t *out);

/*
 * validate command and execute it
 */
int ExecuteCommand(const Commands_t *command);

#endif