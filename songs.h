#ifndef SONGS_H
#define SONGS_H

typedef struct song {
    int Id;
    char title[100];
    char artist[50];
    char genre[50];
    char duration[20];
    struct song *next;
    struct song *prev;
} song;

song* createsong(int id,char* title,char* art,char* genre,char *dur);
void buildqueue(song *list, song *picked);
void listsongs(song* head);
song* loadsongs();
void freetmp(song* head);
void playprev();
void playnext();
song* searchsong(song* head, char* type, char* keyword);
song* getsong(song* head,int num);
void addsongtolibrary(void);
extern song* playqueue;
extern song* currsong;

#endif
