#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "albums.h"
#include "songs.h"
#include "log.h"
#include "playlists.h"

void menu() {
    printf("---------------------------------\n");
    printf("~> MENU:\n");
    printf("1. List Songs\n");
    printf("2. Search Song\n");
    printf("3. List Albums\n");
    printf("4. Create Album\n");
    printf("5. Open Album\n");
    printf("6. Create Playlist\n");
    printf("7. Open Playlist\n");
    printf("8. Show Command Log\n");
    printf("9. Exit\n");
    printf("---------------------------------\n");
}

int main() {

    song *lib = loadsongs();
    album *albhead = loadalbums();
    playlist *plhead = loadplaylists();

    char task[100];
    int choice;

    printf("C-Unplugged!\n");

    while (1) {
        printf("~> Enter the no. of your choice\n");
        menu();
        printf("~> ");
        fgets(task, sizeof(task), stdin);
        choice = atoi(task);
        if (choice < 1 || choice > 9) {
            printf("~> Please choose a valid number\n");
            continue;
        }

        switch (choice) {
        case 1:
            listsongs(lib);
            printf("\n");
            break;
    //-------------------------------------------------
        case 2: {
            printf("~> Search syntax: <title/artist/genre> <keyword>\n~> ");
            fgets(task, sizeof(task), stdin);
            task[strcspn(task, "\n")] = 0;

            char *type = strtok(task, " ");
            char *key = strtok(NULL, " ");

            if (!type || !key) {
                printf("~> invalid search syntax\n");
                break;
            }

            song *result = searchsong(lib, type, key);

            if (!result) {
                printf("~> no matching songs\n");
                break;
            }

            listsongs(result);

            printf("~> Enter song number to play (0 = skip): ");
            fgets(task, sizeof(task), stdin);
            int n = atoi(task);

            if (n > 0) {
                song *picked = getsong(result, n);

                if (!picked) {
                    printf("~> invalid song number\n");
                    freetmp(result);
                    break;
                }

                song *orig = lib;
                while (orig && orig->Id != picked->Id)
                    orig = orig->next;

                buildqueue(lib, orig);

                printf("~> Now playing: %s - %s\n",
                       orig->title, orig->artist);

                char b[100];
                sprintf(b, "played %d", orig->Id);
                logcmd(b);
            }

            freetmp(result);
            printf("\n");
            break;
        }
    //-------------------------------------------------
        case 3:
            listalbums(albhead);
            printf("\n");
            break;
    //-------------------------------------------------
        case 4:
            printf("~> Enter album name\n~> ");
            fgets(task, sizeof(task), stdin);
            task[strcspn(task, "\n")] = 0;
            insertalbum(&albhead, createalbum(task));
            printf("\n");
            break;
    //-------------------------------------------------
        case 5:
            openalbum(albhead, lib);
            printf("\n");
            break;
    //-------------------------------------------------
        case 6:
            printf("~> Enter playlist name\n~> ");
            fgets(task, sizeof(task), stdin);
            task[strcspn(task, "\n")] = 0;
            createplaylist(task);
            printf("\n");
            break;
    //-------------------------------------------------
        case 7: {
            listplaylists(plhead);

            printf("~> enter playlist no:\n~> ");
            fgets(task, sizeof(task), stdin);
            int pno = atoi(task);

            playlist *pick = getplaylist(plhead, pno);

            if (!pick) {
                printf("~> invalid playlist no\n");
                break;
            }

            playlist *full = loadplaylist(pick->Id, lib);
            openplaylist(full, lib);

            printf("\n");
            break;
        }
    //-------------------------------------------------
        case 8:
            showlog();
            printf("\n");
            break;
    //------------------------------------------------
        case 9:
            printf("~> Thank you for your visit :)\n");
            return 0;
        }
    }

    return 0;
}
