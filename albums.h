#ifndef ALBUMS_H
#define ALBUMS_H

typedef struct album {
    char name[50];
    struct album *next;
    struct album *prev;
    struct album *nsong;
} album;

album* createalbum(char nam);
album* searchal(album* head,char name);

#endif
