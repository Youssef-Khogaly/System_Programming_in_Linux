
#ifndef _LIST_H_
#define _LIST_H_ 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct node
{

    struct node *next;
    char *key;
    char *val;
    size_t keyLen; // exclude null terminator
    size_t ValLen; // exclude null terminator
} node_t;

typedef struct
{
    node_t *root;
} list_t;

/*
    must use to create new list
    example
    list_t* list = list_create();
    freeing list_t* is user responsability
*/
list_t *list_create();

/*
    if key doesnot exist will add it to the list
    if key exist will overwrite val
*/
void list_Append(list_t **list, char *key, char *val);

void list_Delete(list_t **list, char *key);
/*
    return null if key doesnt exist
    or list == null or key == null
*/
char *list_GetVal(list_t *list, char *key);
void list_clear(list_t **list);

#endif
