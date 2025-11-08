#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "songs.h"

song* createsong(char title,char art){

    song* new=malloc(sizeof(song));
    if ((new)==NULL)
    {
        printf("memory alloc failed");
        return NULL;
    }
    strcpy(new->title,title);
    strcpy(new->artist,art);
    new->next=NULL; new->prev=NULL;
    return new;
}

