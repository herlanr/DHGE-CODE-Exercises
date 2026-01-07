#include <stdio.h>
#include <stdlib.h>

void dezimalAusgeben(int zahl);

int main(int argc, const char *argv[]){

    for (int i = 1; i < argc; ++i) {
        dezimalAusgeben(atoi(argv[i]));
        putchar('\n'); 
    }  

    exit(EXIT_SUCCESS);
}

void dezimalAusgeben(int zahl){

    if(zahl > 10){

        dezimalAusgeben(zahl/10);

        zahl = zahl % 10;
    }

    putchar(zahl + '0');
    printf(" ");

}