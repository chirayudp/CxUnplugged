#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "albums.h"
#include "songs.h"
#include "playlists.h"
void menu(){
    printf("~> Menu\n");
    printf("000000000000000000000000000000000\n");
    printf("1. List Songs\n");
    printf("2. Search Song\n");
    printf("3. List Albums\n");
    printf("4. Create Album\n");
    printf("5. Open Album\n");
    printf("6. Create Playlist\n");
    printf("7. Open Playlist\n");
    printf("8. Show Command Log\n");
    printf("9. Exit\n");
    printf("000000000000000000000000000000000\n");
    return ;

}

// 0000000000000000000000000000000000000000000000000000000000000000000000000

int main() {
    song* lib=loadsongs();
    song* currlist = lib;
    char task[50];
    int choice;
    printf("C-Unplugged!\n");
    while (1) {
        printf("Enter the no. of ur choice\n");

        menu(); //
        
        printf("~> ");
        fgets(task, sizeof(task), stdin);
        choice = atoi(task);
        if (choice < 1 || choice >15)
        {
            printf("Please choose a valid no.");
            continue;
        }
        switch (choice){
        case 1://listing library
            listsongs(lib);
            break;
        case 2:{// search
            currlist = lib;
            fgets(task, sizeof(task), stdin);
            char* cmd=strtok(task," ");
            printf("Search syntax: <title/artist/genre> <keyword>\n");
            printf("~> ");

                char* type = strtok(task, " ");      
                char* key  = strtok(NULL, " ");   
                if (type == NULL || key == NULL) {
                    printf("Search syntax: <title/artist/genre> <keyword>\n");
                    continue;
                }

                song * result= searchsong(currlist,type,key);//stores search results

                if (result == NULL) {
                    printf("No matching songs found.\n");
                } 
                else {  
                    printf("Search Results:\n");
                    listsongs(result);  

                    printf("Enter song number (0 to skip): ");
                    fgets(task, sizeof(task), stdin);
                    int num = atoi(task);

                    if (num > 0) {
                        song* picked = getsong(result, num);
                        if (picked == NULL) {
                            printf("Invalid song number.\n");
                        } else {
                            printf("You selected: %s - %s\n", picked->title, picked->artist);
                        }
                    }

                }
                freetmp(result);

            break;
        }
        case 3:
            listalbums();
            break;

        case 4:
            createalbum();
            break;
        case 5:
            openalbum();
            break;
        case 6:
            createplaylist();
            break;
        case 7:
            openplaylist();
            break;
        case 8:
            showlog();
            break;
        case 9:
            printf("Thank u for ur visit :)");
            return 0;

        
        default:
            break;
        }

    }

    printf("Thank you for your visit :)\n");
    return 0;
}
