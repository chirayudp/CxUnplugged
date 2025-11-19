#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "albums.h"
#include "songs.h"
#include "playlists.h"
void menu(){
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
    return ;
}
// -------------------------------------------------------------------------
int main() {
    song* lib=loadsongs();
    song* currlist = lib;
    album* albhead = loadalbums();  
    char task[100];
    int choice;
    printf("C-Unplugged!\n");
    while (1) {
        printf("Enter the no. of ur choice\n");

        menu(); //
        
        printf("~> ");
        fgets(task, sizeof(task), stdin);
        choice = atoi(task);
        if (choice < 1 || choice > 9)
        {
            printf("Please choose a valid no.");
            continue;
        }
        switch (choice){
        case 1://listing library
            listsongs(lib);
            printf("\n");
            break;

        case 2:{// search
            printf("Search syntax: <title/artist/genre> <keyword>\n");
            printf("~> ");
            fgets(task, sizeof(task), stdin);
            task[strcspn(task, "\n")] = 0;
            char* type = strtok(task, " ");      
            char* key  = strtok(NULL, " ");   
            if (type == NULL || key == NULL) {
                printf("Search syntax: <title/artist/genre> <keyword>\n");
                continue;
            }

            song * result= searchsong(lib,type,key);//to store search res

            if (result == NULL) {
                printf("No matching songs found.\n");
            } 
            else {  
                printf("Search Results:\n");
                listsongs(result);  

                printf("Enter song number (0 to skip): ");
                fgets(task, sizeof(task), stdin);
                int num = atoi(task);

                if (num >0 ) {
                    song* picked = getsong(result, num);
                    if (picked == NULL) {
                        printf("Invalid song number.\n");
                    } else {
                        printf("You selected: %s - %s\n", picked->title, picked->artist);
                    }
                }

            }
            freetmp(result);
            printf("\n");
            break;
        }
        case 3:
            listalbums(albhead);
            printf("\n");
            break;

        case 4:
        printf("Enter album name\n~> ");
            fgets(task, sizeof(task), stdin);
            task[strcspn(task,"\n")]=0;
            album* new =createalbum(task);
            insertalbum(&albhead,new);
            printf("\n");
            break;
        case 5:
            // openalbum();
            printf("\n");
            break;
        case 6:
            // createplaylist();
            printf("\n");
            break;
        case 7:
            // openplaylist();
            printf("\n");
            break;
        case 8:
            // showlog();
            printf("\n");
            break;
        case 9:
            printf("Thank u for ur visit :)");
            printf("\n");
            return 0;

        
        default:
            printf("\n");
            break;
        }

    }

    printf("Thank you for your visit :)\n");
    return 0;
}
