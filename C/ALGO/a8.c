#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 32000

typedef struct Liste{
    char *head;
    char *tail;
} Liste;

typedef struct Zeile{
    char *fileName;
    int zeilenNummer;
    char *text;
    struct Zeile *next;
} Zeile;

void anhaengen(Liste liste, char fileName, int zeilenNummer, char text);

void fileHandeln(Liste liste, char fileName);

void ausgeben(Liste liste);

int main(int argc, const char *argv[]){

    Liste liste[MAX_LEN] = {};

    exit(EXIT_SUCCESS);
}

void anhaengen(Liste liste, char fileName, int zeilenNummer, char text){

    Zeile *zeile = malloc(sizeof(struct Liste));

    zeile->text = strdup(text);

    zeile->fileName = fileName;

    zeile->zeilenNummer = zeilenNummer;

}

void fileHandeln(Liste liste, char fileName){

    char tempZeilenText[MAX_LEN];

    FILE *f;

    if(fopen(fileName, "r") == NULL){
        fprint(stderr, "Cannot read the file");
        exit(EXIT_FAILURE);
    }

    int n = 0;

    while(fgets(tempZeilenText, sizeof(tempZeilenText), fileName) != NULL){

        anhaengen(liste, fileName, n, tempZeilenText);

        ++n;
    }

    fclose(fileName);
}

void ausgeben(Liste liste){


}