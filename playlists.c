#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "playlists.h"
#include "songs.h"

playlist* createplaylist(char* nam){
    playlist* new=malloc(sizeof(playlist));
    if ((new)==NULL)
    {
        printf("memory alloc failed");
        return NULL;
    }
    strcpy(new->name,nam);
    new->next=NULL;
    new->prev=NULL;
    return new;
}

playlist* searchpl(playlist* head,char* nam){
    playlist* tmp = head;
    while (tmp!=NULL)
    {
        if (tmp->name==nam)
        {
            break;
        }
        
        tmp=tmp->next;
    }
    return tmp ;
}



