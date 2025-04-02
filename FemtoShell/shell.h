
#ifndef _SHELL_H_
#define _SHELL_H_
/*******Includes***********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <echo.h>
#include <errno.h>
#include <tokenizer.h>
/****************defines**************************/
#define INPUT_BUFFER_INIT_SIZE (256)

/*************User Defined types***************/

/****************Macros**************************/

/*******************Interfaces******************** */

/*
 * validate command and execute it
 */
int ExecuteCommand(const Commands_t *command);

#endif