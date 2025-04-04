#include "list.h"

static node_t *CreateNode(char *key, char *val)
{

    node_t *node = (node_t *)malloc(1 * sizeof(node_t));
    if (node)
    {
        if (key)
        {
            node->keyLen = strlen(key);
            node->key = (char *)malloc((node->keyLen + 1) * sizeof(char));
            strncpy(node->key, key, node->keyLen);
            node->key[node->keyLen] = 0; // null terminator
        }
        else
        {
            node->key = NULL;
            node->keyLen = 0;
        }
        if (val)
        {
            node->ValLen = strlen(val);
            node->val = (char *)malloc((node->ValLen + 1) * sizeof(char));
            strncpy(node->val, val, node->ValLen);
            node->val[node->ValLen] = 0; // null terminator
        }
        else
        {
            node->val = NULL;
            node->ValLen = 0;
        }
        node->next = NULL;
    }
    return node;
}

list_t *list_create()
{
    list_t *root = (list_t *)malloc(1 * sizeof(list_t));
    root->root = NULL;
    return root;
}

/*
    if key doesnot exist will add it to the list
    if key exist will overwrite val


    if key exist
    if the old value len >= new val len
    will not reallocate memory
    will copy new val to old val
    and valLen will not be updated
*/
void list_Append(list_t **list, char *key, char *val)
{
    if (list == NULL || key == NULL)
    {
        if (list == NULL)
            fprintf(stderr, "error null list\n");
        else
            fprintf(stderr, "error null key or val\n");
        return;
    }
    // empty list
    if ((*list)->root == NULL)
    {
        (*list)->root = CreateNode(key, val);
    }
    else
    {
        // search for  key
        node_t *temp = (*list)->root;
        size_t usr_keyLen = strlen(key);
        while (temp)
        {
            if (temp->keyLen == usr_keyLen && (strncmp(temp->key, key, temp->keyLen) == 0))
            {

                size_t newValSize = strlen(val);
                free(temp->val);
                temp->val = (char *)malloc((newValSize + 1) * sizeof(char));
                temp->ValLen = newValSize;
                strncpy(temp->val, val, temp->ValLen);
                temp->val[temp->ValLen] = 0;
                break;
            }
            else if (temp->next == NULL) // key is not in the list
            {
                temp->next = CreateNode(key, val);
                break;
            }
            temp = temp->next;
        }
    }

    return;
}
char *list_GetVal(list_t *list, char *key)
{
    if (list == NULL || key == NULL)
        return NULL;
    // search for  key
    node_t *temp = list->root;
    size_t usr_keyLen = strlen(key);
    while (temp)
    {
        if (temp->keyLen == usr_keyLen && (strncmp(temp->key, key, temp->keyLen) == 0))
        {
            return temp->val;
        }
        else
            temp = temp->next;
    }

    return NULL;
}
void list_clear(list_t **list)
{
    if (NULL == (*list) || NULL == (*list)->root)
        return;
    node_t *temp = (*list)->root;
    node_t *temp_next = NULL;

    while (temp)
    {
        temp_next = temp->next;
        if (temp->key)
            free(temp->key);
        if (temp->val)
            free(temp->val);
        free(temp);
        temp = temp_next;
    }

    return;
}