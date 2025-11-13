#ifndef PLAYLISTS_H
#define PLAYLISTS_H
#include "songs.h"
typedef struct playlist {
    char name[50];
    struct playlist *next;
    struct playlist *prev;
    song *sng;
} playlist;

playlist* createplaylist(char* nam);
playlist* searchpl(playlist* head,char* name);
#endif
