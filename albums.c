#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "albums.h"
#include "songs.h"
#include "log.h"

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

album *createalbum(char *name)
{
    ////
    FILE* alb= fopen("albums.txt","r+");
    char line[100];
    fgets(line, sizeof(line) ,alb);
    int cnt = atoi(line);
    int nid=cnt+1;
    fseek(alb, 0, SEEK_SET);
    fprintf(alb, "%d\n", nid);

    fseek(alb, 0, SEEK_END);
    fprintf(alb, "%d\n%s\n\n", nid, name);

    fclose(alb);
    char fname[100];
    snprintf(fname,sizeof(fname), "albums/a%d.txt", nid);
    FILE* alb2= fopen(fname,"w");fclose(alb2);
    ////
    album *new = cal(nid,name);
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

album* getalbum(album* head, int n) {
    int c = 1;
    album* tmp =head;
    while (tmp != NULL) {
        if (c == n) return tmp;
        c++;
        tmp = tmp->next;
    }
    return NULL;
}


album *searchal(album *head, char *name)
{
    album *tmp = head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->name, name) == 0)
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

    char line[1100]; 
    album *head=NULL;
    album* pre = head;
    fgets(line, sizeof(line), alb);
    while (1) {
        
        if (fgets(line, sizeof(line), alb) == NULL)
            break;
        if (strcmp(line, "\n") == 0)
            continue;

        int id = atoi(line); 
        // printf("%s",line);

        char aname[1100];
        if (fgets(aname, sizeof(aname), alb) == NULL) break;
        aname[strcspn(aname, "\n")] = 0;


        fgets(line, sizeof(line), alb);

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
void loadalbumsongs(album *alb, song *lib)
{
    if (alb == NULL) return;   

    char fname[100];
    snprintf(fname, sizeof(fname), "albums/a%d.txt", alb->Id);

    FILE *alf = fopen(fname, "r");
    if (alf == NULL) {
        alb->sng = NULL;
        return;
    }

    char line[1100];
    song *head = NULL;
    song *pre  = head;

    while (1)
    {
        if (fgets(line, sizeof(line), alf) == NULL)break;
        if (strcmp(line, "\n") == 0)continue;// to skip the xtra blank lines seperating albums
            
        int sid = atoi(line);  
        if (sid == 0) continue;
        song *tmp = lib;// searching song in lib
        while (tmp && tmp->Id != sid)
            tmp = tmp->next;
        
        if (tmp == NULL) continue;
        
        song *node = createsong(tmp->Id, tmp->title, tmp->artist, tmp->genre,tmp->duration);
        if (head == NULL) {
            head = node;
            pre  = node;
        } else {
            pre->next = node;
            node->prev = pre;
            pre = node;
        }
    }

    fclose(alf);
    alb->sng = head;  
    return ;
}

void savealbumsongs(album *alb){
    if (alb ==NULL) return;

    char fname[100];
    snprintf(fname, sizeof(fname), "albums/a%d.txt", alb->Id);

    FILE *alf =fopen(fname, "w");
    if (alf ==NULL) {
        printf("Error opening %s\n", fname);
        return;
    }
    song *tmp = alb->sng;
    while (tmp != NULL)
    {
        fprintf(alf,"%d\n",tmp->Id);
        tmp =tmp->next;
    }
    fclose(alf);
    return ;
}

void addsongalbum(album *alb, song *lib)
{
    if (alb == NULL) {
        printf("no album is selected\n");
        return;
    }

    printf("adding song to album: %s\n", alb->name);
    listsongs(lib);
    char line[100];
    printf("Enter the song number to add: ");
    fgets(line, sizeof(line), stdin);
    int num = atoi(line);

    if (num <= 0) {
        printf("Invalid number\n");
        return;
    }
    int c = 1;
    song *tmp = lib;
    while (tmp != NULL && c != num) {
        tmp = tmp->next;
        c++;
    }
    if (tmp == NULL) {
        printf("Song not found\n");
        return;
    }
    song *nn = createsong(tmp->Id, tmp->title, tmp->artist, tmp->genre,tmp->duration);
    if (alb->sng == NULL) {
        alb->sng = nn;
    }
    else {
        song *t2 = alb->sng;
        while (t2->next != NULL) {
            t2 = t2->next;
        }
        t2->next = nn;
        nn->prev = t2;
    }
    savealbumsongs(alb);

    printf("done!!\n");
}

void deletesongalbum(album *alb)
{
    if (alb == NULL) {
        printf("no album opened\n");
        return;
    }

    if (alb->sng == NULL) {
        printf("album has no songs\n");
        return;
    }

    printf("songs inside album:\n");
    listsongs(alb->sng);

    printf("enter the song number to delete:\n~> ");

    char line[100];
    fgets(line, sizeof(line), stdin);
    int num = atoi(line);

    if (num <= 0) {
        printf("invalid number\n");
        return;
    }

    song *tmp = alb->sng;
    int c = 1;
    // return ;
    while (tmp != NULL && c != num) {
        tmp = tmp->next;
        c++;
    }

    if (tmp == NULL) {
        // printf("here!! num=%d\n", num); 
        printf("song not found\n");
        return;
    }
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    else alb->sng = tmp->next;   
        
        // printf("deleted... \n"); 
    if (tmp->next != NULL)tmp->next->prev = tmp->prev;
    free(tmp);
    printf("successfully removed the song\n");

    savealbumsongs(alb);
    return ;
}



void openalbum(album *albhead, song *lib)
{
    char task[1100];
    int num;

    listalbums(albhead);
    printf("enter album number:\n~> ");
    fgets(task, sizeof(task), stdin);
    num = atoi(task);

    album *alb = getalbum(albhead, num);
    if (alb == NULL) {
        printf("invalid album number\n");
        return;
    }

    loadalbumsongs(alb, lib);
    printf("opened album: %s\n", alb->name);

    while (1)
    {
        printf("\n------ album menu ------\n");
        printf("1. list songs\n");
        printf("2. add song\n");
        printf("3. delete song\n");
        printf("4. play a song\n");         
        printf("5. search song inside album\n");
        printf("6. exit album\n");
        printf("--------------------------------\n");
        printf("~> ");

        fgets(task, sizeof(task), stdin);
        int ch = atoi(task);

        switch (ch)
        {
        case 1:
            listsongs(alb->sng);
            break;

        case 2:
            addsongalbum(alb, lib);
            break;

        case 3:
            deletesongalbum(alb);
            break;

        case 4: {
            if (alb->sng == NULL) {
                printf("album empty\n");
                break;
            }

            listsongs(alb->sng);
            printf("enter song number to play:\n~> ");
            fgets(task, sizeof(task), stdin);
            int n = atoi(task);

            if (n <= 0) {
                printf("invalid\n");
                break;
            }

            song *picked = getsong(alb->sng, n);
            if (picked == NULL) {
                printf("invalid\n");
                break;
            }

            buildqueue(alb->sng, picked);  
            printf("now playing: %s - %s\n", picked->title, picked->artist);

            char b[100];
            sprintf(b, "played %d from album %d", picked->Id, alb->Id);
            logcmd(b);
            break;
        }

        case 5: {
            printf("~> search syntax: <title/artist/genre> <keyword>\n~> ");
            fgets(task, sizeof(task), stdin);
            task[strcspn(task, "\n")] = 0;

            char *type = strtok(task, " ");
            char *key  = strtok(NULL, " ");

            if (type == NULL || key == NULL) {
                printf("~> invalid search syntax\n");
                break;
            }

            song *res = searchsong(alb->sng, type, key);

            if (res == NULL) {
                printf("~> no matching songs\n");
                break;
            }

            listsongs(res);

            printf("~> enter song number to play (0 = skip): ");
            fgets(task, sizeof(task), stdin);
            int n = atoi(task);

            if (n <= 0) {
                freetmp(res);
                break;
            }

            song *picked = getsong(res, n);

            if (picked == NULL) {
                printf("~> invalid choice\n");
                freetmp(res);
                break;
            }

            buildqueue(alb->sng, picked);
            printf("~> now playing: %s - %s\n", picked->title, picked->artist);

            char b[100];
            sprintf(b, "played %d from album %d", picked->Id, alb->Id);
            logcmd(b);

            freetmp(res);
            break;
        }

        case 6:
            printf("~> leaving album: %s\n", alb->name);
            return;

        default:
            printf("~> invalid choice\n");
            break;
        }
    }
}




