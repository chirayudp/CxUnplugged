#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "playlists.h"
#include "songs.h"
#include "log.h"

playlist* createplaylist(char* nam)
{
    FILE *fp;
    char buf[100];
    int cnt;
    int nid;

    fp = fopen("playlists.txt", "r+");
    if (fp == NULL) {
        fp = fopen("playlists.txt", "w+");
        fprintf(fp, "0\n");
        fseek(fp, 0, SEEK_SET);
    }

    fgets(buf, sizeof(buf), fp);
    cnt = atoi(buf);
    nid = cnt + 1;

    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "%d\n", nid);

    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%d\n%s\n\n", nid, nam);

    fclose(fp);

    char fname[100];
    sprintf(fname, "playlists/p%d.txt", nid);
    FILE *fp2 = fopen(fname, "w");
    fclose(fp2);

    playlist *pl = malloc(sizeof(playlist));
    if (pl == NULL)
        return NULL;

    pl->Id = nid;
    strcpy(pl->name, nam);
    pl->next = NULL;
    pl->prev = NULL;
    pl->sng = NULL;
    pl->currsong = NULL;

    return pl;
}
playlist* getplaylist(playlist* head, int n)
{
    int c = 1;
    playlist *tmp = head;
    while (tmp != NULL) {
        if (c == n) return tmp;
        c++;
        tmp = tmp->next;
    }
    return NULL;
}

playlist* loadplaylists()
{
    FILE *fp;
    char tmp[200];
    int id;

    fp = fopen("playlists.txt", "r");
    if (fp == NULL) {
        return NULL;
    }

    fgets(tmp, sizeof(tmp), fp); // skip count

    playlist *head = NULL;
    playlist *pre = NULL;

    while (1)
    {
        if (fgets(tmp, sizeof(tmp), fp) == NULL)
            break;

        if (strcmp(tmp, "\n") == 0)
            continue;

        id = atoi(tmp);

        char pname[100];
        if (fgets(pname, sizeof(pname), fp) == NULL)
            break;

        pname[strcspn(pname, "\n")] = 0;

        fgets(tmp, sizeof(tmp), fp);

        playlist *pl = malloc(sizeof(playlist));
        if (pl == NULL) {
            // printf("malloc fail\n");
            continue;
        }

        pl->Id = id;
        strcpy(pl->name, pname);
        pl->sng = NULL;
        pl->currsong = NULL;
        pl->next = NULL;
        pl->prev = NULL;

        if (head == NULL) {
            head = pl;
            pre = pl;
        } else {
            pre->next = pl;
            pl->prev = pre;
            pre = pl;
        }
    }

    fclose(fp);
    return head;
}

playlist* loadplaylist(int pid, song* lib)
{
    char fname[100];
    sprintf(fname, "playlists/p%d.txt", pid);

    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
    {
        return NULL;    
    }

    playlist *pl = malloc(sizeof(playlist));
    if (pl == NULL)
    {
        fclose(fp);
        return NULL;
    }

    pl->Id = pid;       
    pl->next = NULL;
    pl->prev = NULL;
    pl->sng = NULL;
    pl->currsong = NULL;

    char l1[200];

    if (fgets(l1, sizeof(l1), fp) == NULL) {
        fclose(fp);
        return pl;
    }

    l1[strcspn(l1, "\n")] = 0;
    strcpy(pl->name, l1);

    char buf[50];  
    song *h = NULL;
    song *p = NULL;

    while (1)
    {
        if (fgets(buf, sizeof(buf), fp) == NULL)
            break;

        if (strcmp(buf, "\n") == 0)
            continue;

        int sid = atoi(buf);
        if (sid == 0)
            continue;

        song *ts = lib;
        while (ts != NULL && ts->Id != sid)
        {
            ts = ts->next;
        }

        if (ts == NULL)
            continue;

        song *nn = createsong(ts->Id, ts->title, ts->artist, ts->genre,ts->duration);

        if (h == NULL)
        {
            h = nn;
            p = nn;
        }
        else
        {
            p->next = nn;
            nn->prev = p;
            p = nn;
        }
    }

    pl->sng = h;
    pl->currsong = h;

    fclose(fp);
    return pl;
}

playlist* searchpl(playlist* head,char* nam){
    playlist* tmp = head;
    while (tmp!=NULL)
    {
        if (strcmp(tmp->name, nam) == 0)
        {
            break;
        }
        
        tmp=tmp->next;
    }
    return tmp ;
}

// void playnext(song **currsong)
// {
//     song *tmp = *currsong;

//     if (tmp == NULL) {
//         printf("no song is currently selected\n");
//         return;
//     }

//     if (tmp->next == NULL) {                
//         while (tmp->prev != NULL)          // go to head
//             tmp = tmp->prev;
//         *currsong = tmp;                    // loop back to start
//     }
//     else {
//         tmp = tmp->next;
//         *currsong = tmp;
//     }

//     printf("now playing: %s - %s\n", tmp->title, tmp->artist);
// }

// void playprev(song **currsong)
// {
//     song *tmp = *currsong;

//     if (tmp == NULL) {
//         printf("no song is currently selected\n");
//         return;
//     }

//     if (tmp->prev == NULL) {                
//         while (tmp->next != NULL)          // go to last song
//             tmp = tmp->next;
//         *currsong = tmp;                    // loop to end
//     }
//     else {
//         tmp = tmp->prev;
//         *currsong = tmp;
//     }

//     printf("now playing: %s - %s\n", tmp->title, tmp->artist);
// }

// void buildqueue(song *list, song *picked, song **playhead, song **currsong)
// {
//     song *tmp = list;
//     song *h = NULL;
//     song *pre = NULL;

//     while (tmp != NULL)
//     {
//         song *n = createsong(tmp->Id, tmp->title, tmp->artist, tmp->genre,tmp->duration);

//         if (h == NULL) {
//             h = n;
//             pre = n;
//         } else {
//             pre->next = n;
//             n->prev = pre;
//             pre = n;
//         }

//         if (tmp->Id == picked->Id)
//             *currsong = n;

//         tmp = tmp->next;
//     }

//     *playhead = h;
// }

void addsongplaylist(playlist *pl, song *lib)
{
    if (pl == NULL) {
        printf("no playlist selected\n");
        return;
    }

    song *tlib = lib;
    listsongs(tlib);

    char line[50];
    printf("enter song no: ");
    fgets(line, sizeof(line), stdin);
    int k = atoi(line);

    int cnt = 1;
    song *tmp = tlib;
    while (tmp != NULL && cnt != k) {
        tmp = tmp->next;
        cnt++;
    }

    if (tmp == NULL) {
        printf("invalid song\n");
        return;
    }

    song *news = createsong(tmp->Id, tmp->title, tmp->artist, tmp->genre ,tmp->duration);

    if (pl->sng == NULL) {
        pl->sng = news;
        pl->currsong = news;
    } else {
        song *x = pl->sng;
        while (x->next != NULL)
            x = x->next;

        x->next = news;
        news->prev = x;
    }

    printf("added!!\n");
}

void deletesongplaylist(playlist *pl)
{
    if (pl == NULL || pl->sng == NULL) {
        printf("playlist empty\n");
        return;
    }

    listsongs(pl->sng);

    char buf[50];
    printf("enter song no to delete: ");
    fgets(buf, sizeof(buf), stdin);
    int n = atoi(buf);

    int c = 1;
    song *tmp = pl->sng;

    while (tmp != NULL && c != n) {
        tmp = tmp->next;
        c++;
    }

    if (tmp == NULL) {
        printf("invalid no\n");
        return;
    }

    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    else
        pl->sng = tmp->next;

    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;

    if (pl->currsong == tmp)
        pl->currsong = pl->sng;

    free(tmp);

    printf("done\n");
}

void listplaylists(playlist *head)
{
    if (head == NULL) {
        printf("no playlists available\n");
        return;
    }

    playlist *tmp = head;
    int c = 1;

    printf("playlists:\n");
    while (tmp != NULL) {
        printf("%d. %s\n", c++, tmp->name);
        tmp = tmp->next;
    }
}

void openplaylist(playlist *pl, song *lib)
{
    if (pl == NULL) {
        printf("invalid playlist\n");
        return;
    }

    int choice;
    char buf[50];

    while (1) {
        printf("\nplaylist: %s\n", pl->name);
        printf("1. list songs\n");
        printf("2. add song\n");
        printf("3. delete song\n");
        printf("4. play next\n");
        printf("5. play prev\n");
        printf("6. exit playlist\n");
        printf("~> ");

        fgets(buf, sizeof(buf), stdin);
        choice = atoi(buf);

        if (choice == 1) {
            listsongs(pl->sng);
        }
        else if (choice == 2) {
            addsongplaylist(pl, lib);
        }
        else if (choice == 3) {
            deletesongplaylist(pl);
        }
        else if (choice == 4) {
            currsong = pl->currsong;  
            playnext();
            pl->currsong = currsong;  
        }
        else if (choice == 5) {
            currsong = pl->currsong;  
            playprev();
            pl->currsong = currsong; 
            
        }
        else if (choice == 6) {
            break;
        }
        else {
            printf("invalid\n");
        }
    }
}

void saveplaylist(playlist *pl)
{
    if (pl == NULL)
        return;             

    char fname[100];
    sprintf(fname, "playlists/p%d.txt", pl->Id);

    FILE *fp = fopen(fname, "w");
    if (fp == NULL)
    {
        return;
    }

    fprintf(fp, "%s\n", pl->name);

    song *ts = pl->sng;

    while (ts != NULL)
    {
        fprintf(fp, "%d\n", ts->Id);
        ts = ts->next;
    }

    fclose(fp);
}

