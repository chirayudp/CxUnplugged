#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "playlists.h"

playlist* createalbum(char nam){

    playlist* new=malloc(sizeof(playlist));
    if ((new)==NULL)
    {
        printf("memory alloc failed");
        return NULL;
    }
    strcpy(new->name,&nam);
    new->next=NULL;
    new->prev=NULL;
    return new;
}

playlist* searchal(playlist* head,char name){
    playlist* tmp = head;
    while (tmp!=NULL)
    {
        tmp=tmp->next;
    }
    
}



