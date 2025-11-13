#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "albums.h"
#include "songs.h"
#include "playlists.h"

int main() {
    song* lib=loadsongs();
    char task[100];
    printf("C-Unplugged!\n");
    while (1) {
        printf("~> ");
        fgets(task, sizeof(task), stdin);
        task[strcspn(task, "\n")] = 0;  
        char* cmd = strtok(task," ");

// 0000000000000000000000000000000000000000000000000000000000000000000000000
        if (strcmp(cmd, "ls") == 0){
            listsongs(lib);
        } 
// 0000000000000000000000000000000000000000000000000000000000000000000000000

        else if (strcmp(cmd, "ca") == 0)
            printf("[Album will be created]\n");

        else if (strcmp(cmd, "oa") == 0){
            printf("opening Album \n");
            
        }
            
        else if (strcmp(cmd, "ss") == 0)
            printf("search songs - songs that matches will appear\n");
        
        else if (strcmp(cmd, "pp") == 0)
            printf("play playlist\n");

        else if (strcmp(cmd, "next") == 0)
            printf("next song\n");
        
        else if (strcmp(cmd, "prev") == 0)
            printf("prev song\n");
        
        else if (strcmp(cmd, "stop") == 0)
            printf("stop song\n");

        else if (strcmp(cmd, "exit") == 0)
            break;

        else{
            printf("List of commands.\n");
            printf(" ls - List songs\n ca - create albums\n exit - to exit.\n ss - search songs\n pp - play playlist");
        }
            
    }

    printf("Thank you for your visit :)\n");
    return 0;
}
        //make a command for listing the songs in the album.
