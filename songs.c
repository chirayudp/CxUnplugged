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
    strcpy(new->title,&title);
    strcpy(new->artist,&art);
    new->next=NULL; new->prev=NULL;

    FILE *fptr= fopen("list_of_songs.txt","a+");
    if (fptr==NULL)
    {
        printf("Error\n");
    }
    fclose(fptr);
   
    return new;
}

void listsongs(){
    printf("List of songs\n");
    FILE *f= fopen("list_of_songs.txt","r");
    if (f==NULL)
    {
        printf("Error\n");
    }
    char line[100];
    while (fgets(line, sizeof(line),f)!= NULL)
    {
        printf("%s",line);
    }
    
    fclose(f);
    return ;
} 
// loadsongs is not finished.
song* loadsongs(){
    FILE *f= fopen("list_of_songs.txt","r");
    if (f==NULL)
    {
        printf("Error\n");
    }
    char line[100];
    while (fgets(line, sizeof(line),f)!= NULL)
    {
        printf("%s",line);
    }
    
    fclose(f);
    return ;
}
