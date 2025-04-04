
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
/****************defines**************************/
#define INPUT_BUFFER_INIT_SIZE (256)

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
void cdCommand(int argc, char *argv[]);
void printEnv();
/*
    adding an existing variable to the environment variables.
*/
void export(Commands_t *comm);
#endif