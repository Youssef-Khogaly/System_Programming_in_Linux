
#ifndef _SHELL_H_
#define _SHELL_H_
/*******Includes***********/

/*Macro Requirements for glibc*/
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <tokenizer.h>
#include <sys/wait.h>
#include <list.h>
#include <ls.h>
#include <cat.h>
#include <cp.h>
#include <mv.h>
#include <cd.h>
#include <pwd.h>
#include <echo.h>
/****************defines**************************/
#define INPUT_BUFFER_INIT_SIZE (256)

/* redirected flags*/
#define STDIN_REDIRECTED (0x2)
#define STDOUT_REDIRECTED (0x4)
#define STDERR_REDIRECTED (0x8)

#define STDIN_REDIRECTED_MASK (0x2)
#define STDOUT_REDIRECTED_MASK (0x4)
#define STDERR_REDIRECTED_MASK (0x8)

/*
 * absolute enviroment path for our built in unix utinlity
 */
#define _ENV_PATH_ ("/home/khogaly/sysPro/System_Programming_in_Linux/PicoShell/bin/")
/*************User Defined types***************/

/****************Macros**************************/

/*******************Interfaces******************** */

/*
 * validate command and execute it
 */
int ExecuteCommand(Commands_t *command);

/*

    return true if its local variabla assign command
    else return false
*/
bool LocalVariableAssignHandler(Commands_t *comm);
void LocalVariableReplace(Commands_t *comm);
/*
    return -1 -> error while redirecting
    return  ->  bitwise or
        STDIN_REDIRECTED
        STDOUT_REDIRECTED
        STDERR_REDIRECTED
    example
    if stdin and stdout are redirected
    return STDIN_REDIRECTED|STDOUT_REDIRECTED

    if no stream redirected return 0
*/
int IO_RedirectionHandler(Commands_t *comm);
void printEnv();
/*
    adding an existing variable to the environment variables.
*/
void export(Commands_t *comm);
#endif