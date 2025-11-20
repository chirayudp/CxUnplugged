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
album* cal(int id, char *name);
album* createalbum(char* nam);
album* searchal(album* head,char* name);
void insertalbum(album **head, album *new);
album* getalbum(album* head, int n);
album* loadalbums();
void loadalbumsongs(album *a, song *lib);
void listalbums(album* head);
void insertalbum(album **head, album *new);
void savealbumsongs(album *alb);
void openalbum(album *albhead, song *lib);
void savealbumsongs(album *alb);
void addsongalbum(album *alb, song *lib);
void deletesongalbum(album *alb);
#endif
