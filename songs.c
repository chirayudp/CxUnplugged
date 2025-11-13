#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "songs.h"

song* createsong(char* title,char* art){

    song* new=malloc(sizeof(song));
    if ((new)==NULL)
    {
        printf("memory alloc failed");
        return NULL;
    }
    strcpy(new->title,title);
    strcpy(new->artist,art);
    new->next=NULL; new->prev=NULL;

    FILE *fptr= fopen("list_of_songs.txt","a+");
    if (fptr==NULL)
    {
        printf("Error\n");
    }
    fclose(fptr);
   
    return new;
}

song* loadsongs(){
    FILE *f= fopen("list_of_songs.txt","r");
    if (f==NULL)
    {
        printf("Error\n");
    }

    char line[100]; 
    song *head=malloc(sizeof(song));
    head->prev=NULL;
    song* tmp = head;
    song* pre = head;
    while (fgets(line, sizeof(line),f)!= NULL)
    {
        char *title=strtok(line,",");
        char* art= strtok(line,NULL);
        tmp = createsong(title,art);
        tmp -> prev = pre;
        pre=tmp;
        tmp= tmp ->next;
        // printf("%s",line);
    }
    
    fclose(f);
    return head ;
}

void listsongs(song * head){
    printf("List of songs\n");
    song* tmp = head;
    while (tmp!=NULL)
    {
        printf("%s\t%s\n",tmp->title,tmp->artist);
        tmp= tmp->next;
    }
    
    return ;
} 