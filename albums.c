#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "albums.h"

album *createalbum(char *nam)
{

    album *new = malloc(sizeof(album));
    if ((new) == NULL)
    {
        printf("memory alloc failed");
        return NULL;
    }
    strcpy(new->name,nam);
    new->next = NULL;
    new->prev = NULL;
    return new;
}

album *searchal(album *head, char *nam)
{
    album *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->name==nam)
        {
            break;
        }
        tmp = tmp->next;
    }
    return tmp ;
}
