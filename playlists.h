#ifndef PLAYLISTS_H
#define PLAYLISTS_H
#include "songs.h"
typedef struct playlist {
    int Id;
    char name[50];
    struct playlist *next;
    struct playlist *prev;
    song *sng;
    song *currsong;
} playlist;

playlist* createplaylist(char* nam);
playlist* searchpl(playlist* head,char* name);
playlist* getplaylist(playlist* head, int n);
// void playnext(song **currsong);
// void playprev(song **currsong);
void addsongplaylist(playlist *pl, song *lib);
void deletesongplaylist(playlist *pl);
void openplaylist(playlist *pl, song *lib);
playlist* loadplaylist(int pid, song* lib) ;
void saveplaylist(playlist *pl);
void listplaylists(playlist *head);
playlist* loadplaylists();

#endif
