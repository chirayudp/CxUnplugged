#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "albums.h"
album* cal(int id, char *name) {
    album *new = malloc(sizeof(album));
    if ((new) == NULL)
    {
        printf("memory alloc failed");
        return NULL;
    }    
    new->Id = id;
    strcpy(new->name,name);
    new->next = NULL;
    new->prev = NULL;
    new->sng = NULL;
    return new;
}

album *createalbum(char *nam)
{
    ////
    FILE* alb= fopen("albums.txt","r+");
    char line[50];
    fgets(line, sizeof(line) ,alb);
    int cnt = atoi(line);
    int nid=cnt+1;
    fseek(alb, 0, SEEK_SET);
    fprintf(alb, "%d\n", nid);

    fseek(alb, 0, SEEK_END);
    fprintf(alb, "%d\n%s\n\n", nid, nam);

    fclose(alb);
    char fname[50];
    snprintf(fname,sizeof(fname), "albums/a%d.txt", nid);
    FILE* alb2= fopen(fname,"w");fclose(alb2);
    ////
    album *new = cal(nid,nam);
    return new;
}
void insertalbum(album **head, album *new){
    if (*head == NULL) {           
        *head = new;
        return ;
    }

    album *tmp = *head;
    while (tmp->next != NULL){
        tmp = tmp->next;
    }
    
    tmp->next = new;
    new->prev = tmp;
}


album *searchal(album *head, char *nam)
{
    album *tmp = head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->name, nam) == 0)
        {
            break;
        }
        tmp = tmp->next;
    }
    return tmp ;
}

album* loadalbums(){
    FILE *alb = fopen("albums.txt", "r");
    if (alb==NULL)
    {
        printf("Error\n");
        return NULL;
    }

    char line[100]; 
    album *head=NULL;
    album* pre = head;
    fgets(line, sizeof(line), alb);
    while (1) {
        
        if (fgets(line, sizeof(line), alb) == NULL)
            break;
        
        // to skip the xtra blank lines seperating albums
        if (strcmp(line, "\n") == 0)
            continue;

        int id = atoi(line); 
        // printf("%s",line);

        char aname[100];
        if (fgets(aname, sizeof(aname), alb) == NULL) break;
        aname[strcspn(aname, "\n")] = 0;


        fgets(line, sizeof(line), alb);//Skip the blank line seperating albums

        album *tmp = cal(id,aname);
        if (head == NULL) {
            head =tmp;
            pre=tmp;
        } 
        else {
            pre->next = tmp;
            tmp->prev = pre;
            pre=tmp;
        }
    }
    
    fclose(alb); 
    return head ;
}



void listalbums(album* head){
    if (head==NULL)
    {
        printf("No album is available\n");
        return ;
    }
    
    printf("List of albums\n");
    album* tmp = head;
    int c=1;
    while (tmp!=NULL)
    {
        printf("%d. %s\n",c++,tmp->name);
        tmp = tmp->next;
    }
    return ;
} 
