#ifndef PLAYLISTS_H
#define PLAYLISTS_H

typedef struct playlist {
    char name[50];
    struct playlist *next;
    struct playlist *prev;
    struct playlist *nsong;
} playlist;

playlist* createalbum(char nam);
playlist* searchal(playlist* head,char name);
#endif
