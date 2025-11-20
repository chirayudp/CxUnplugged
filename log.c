#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "log.h"

void logcmd(char *msg)
{
    FILE *lf = fopen("log.txt", "a");
    if (lf == NULL) return;

    fputs(msg, lf);
    fputs("\n", lf);

    fclose(lf);
}

void showlog()
{
    FILE *lf = fopen("log.txt", "r");
    if (lf==NULL) {
        printf("no logs yet\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), lf))
        printf("%s", line);

    fclose(lf);
}
