#ifndef SONGS_H
#define SONGS_H

typedef struct song {
    char title[50];
    char artist[50];
    struct song *next;
    struct song *prev;
} song;

song* createsong(char title,char art);
void listsongs();
#endif
