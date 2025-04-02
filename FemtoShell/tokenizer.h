#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/****************defines**************************/

#define INIT_ARGV_CAPACITY (32)

/*************User Defined types***************/
typedef struct
{
    int argc;
    char **argv;
    int argvCapacity;
} Commands_t;

typedef enum
{
    SPACE = ' ',
    TAB = '\t'
} Separators_t;

/****************Macros**************************/

#define IS_SEPARATOR(_CHAR) (((SPACE == _CHAR) || (TAB == _CHAR)))

/*******************Interfaces******************** */

/**
 *
 *  Must be called before using any Commands_t variable
 */
void Tokenizer_init(Commands_t *Command);

/*
 @details free  argv[0] till argv[argc-1] and set them to NULL;
          and set argc to 0
*/
void Tokenizer_free_ArgvStrs(Commands_t *command);

/**
 *
 * totally free all Commands_t pointers and set them to null
 * if they aren't freed
 * and set argc & argvcapacity to 0
 */
void Tokenizer_free_all(Commands_t *comm);

/**
 *
 * tokenize user input to argc and argv
 *
 *     return:
            0 - > success
            -1 -> input or out are null ptr
            -2 -> memory allocation faill
            -3 -> size = 0
 */
int Tokenize_Line(char *Line, int size, Commands_t *out);

#endif