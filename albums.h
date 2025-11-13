#ifndef ALBUMS_H
#define ALBUMS_H
#include "songs.h"

typedef struct album {
    char name[50];
    struct album *next;
    struct album *prev;
    song *sng;
} album;

album* createalbum(char* nam);
album* searchal(album* head,char* name);

#endif
