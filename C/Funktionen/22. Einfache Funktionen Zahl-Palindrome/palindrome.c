#include <stdio.h>
#include <stdlib.h>

int umdrehen(int number);

int main(int argc, const char *argv[]){

    int zahl = atoi(argv[1]);

    if(argc != 2){
        fprintf(stderr, "Aufruf: %s Zahl", argv[0]);
        exit(EXIT_FAILURE);
    }

    int zahl2 = 0;
    int count = 0;

    for(int i = 0; i <= zahl; i++){

        zahl2 = umdrehen(i);

        if (zahl2 == i){
            printf("%d und %d\n", i, zahl2);
            count++;
        }
    }

    printf("Count = %d", count);

    exit(EXIT_SUCCESS);
}

int umdrehen(int number){
    
    int ergebnis = 0;
    int ziffer = 0;

    while(number != 0){

        ziffer = number % 10;
        number /= 10;

        ergebnis = ergebnis * 10 + ziffer;
    }

    return ergebnis;
}

