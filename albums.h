#ifndef ALBUMS_H
#define ALBUMS_H
#include "songs.h"

typedef struct album {
    int Id;
    char name[50];
    struct album *next;
    struct album *prev;
    song *sng;
} album;

album* createalbum(char* nam);
album* searchal(album* head,char* name);
album* loadalbums();
void listalbums(album* head);
void insertalbum(album **head, album *new);
#endif
