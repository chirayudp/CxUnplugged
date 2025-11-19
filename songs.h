#ifndef SONGS_H
#define SONGS_H

typedef struct song {
    int Id;
    char title[100];
    char artist[50];
    char genre[50];
    struct song *next;
    struct song *prev;
} song;

song* createsong(int id,char* title,char* art,char* genre);
void listsongs(song* head);
song* loadsongs();
void freetmp(song* head);
song* searchsong(song* head, char* type, char* keyword);
song* getsong(song* head,int num);

#endif
