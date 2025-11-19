#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "songs.h"

void lowercase(char* s){
    int i=0;
    while (s[i]!=0)
    {
        if (s[i]>='A' && s[i]<='Z')  s[i]+=32;
        i++;
    }
    
    
}

song* createsong(int id,char* title,char* art,char* genre){

    song* new=malloc(sizeof(song));
    if ((new)==NULL)
    {
        printf("memory alloc failed!!");
        return NULL;
    }
    new->Id=id;
    strcpy(new->title,title);
    strcpy(new->artist,art);
    strcpy(new->genre,genre);
    new->next=NULL; 
    new->prev=NULL;

    return new;
}

song* loadsongs(){
    FILE *f= fopen("library.txt","r");
    if (f==NULL)
    {
        printf("Error\n");
        return NULL;
    }

    char line[100]; 
    song *head=NULL;
    song* pre = head;
    while (1) {
        
        if (fgets(line, sizeof(line), f) == NULL)
            break;
        
        // to skip the xtra blank lines seperating songs
        if (strcmp(line, "\n") == 0)
            continue;

        int id = atoi(line); 
        // printf("%s",line);

        char title[100];
        if (fgets(title, sizeof(title), f) == NULL) break;
        title[strcspn(title, "\n")] = 0;

        char art[50];
        if (fgets(art, sizeof(art), f) == NULL) break;
        art[strcspn(art, "\n")] = 0;

        char genre[50];
        if (fgets(genre, sizeof(genre), f) == NULL) break;
        genre[strcspn(genre, "\n")] = 0;

        fgets(line, sizeof(line), f);//Skip the blank line seperating songs

        song *tmp = createsong(id,title,art,genre);
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
    
    fclose(f); 
    return head ;
}

void listsongs(song* head){
    printf("List of songs\n");
    song* tmp = head;
    int c=1;
    while (tmp!=NULL)
    {
        printf("%d.%s - %s\n",c++,tmp->title,tmp->artist);
        tmp= tmp->next;
    }
    return ;
} 

void freetmp(song* head){
    song* tmp;
    while (head!=NULL)
    {
        tmp=head;
        
        head= head->next;
        free(tmp);
    }
    
}

song* searchsong(song* head, char* type, char* keyword)
{
    if (!(strcmp(type, "title") == 0 || strcmp(type, "artist") == 0 || strcmp(type, "genre") == 0)) 
    {
        printf("Invalid search type\n");
        return NULL;
    }
    if (head == NULL || type == NULL || keyword == NULL) return NULL;
    
    song *tmp = head;

    song *thead = NULL; 
    song *tail = NULL; 
    char key[50];
    strcpy(key,keyword);
    lowercase(key);

    while (tmp!=NULL)
    {
        char targ[100];
        if (strcmp(type,"title")==0)strcpy(targ,tmp->title);
        else if (strcmp(type,"artist")==0)strcpy(targ,tmp->artist);
        else if (strcmp(type,"genre")==0)strcpy(targ,tmp->genre);

        lowercase(targ);
        
        if (strstr(targ , key)!=NULL)
        {
            song* node= createsong(tmp->Id,tmp->title,tmp->artist,tmp->genre);
            if (thead==NULL)
            {
                thead= node;
                tail = node;
            }
            else{
                tail->next=node;
                node->prev = tail;
                tail=node;
            }

        }
        tmp=tmp->next;
        
    }
    return thead;
    
}

song* getsong(song* head,int num){
    int c=1;
    song* tmp= head;
    while (tmp!=NULL)
    {
        if (num == c)return tmp;
        c++;
        tmp = tmp->next;
    }
    return NULL;
}
