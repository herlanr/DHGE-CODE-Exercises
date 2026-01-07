#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char const *argv[]){

    const int MAX = 100000;
    int n = atoi(argv[1]);

    if(argc != 2){
        fprintf(stderr, "Aufruf: %s n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(!(n > 2) || !(n <= MAX)){
        fprintf(stderr, "Ungultiges n %s", argv[0]);
        exit(EXIT_FAILURE);
    }

    bool prim[MAX];

    //ausfüllen
    for (int i = 0; i <= n; i++){

        prim[i] = true;
    }

    //prüfen und ausgeben
    for (int i = 2; i <= n; i++){

        if(prim[i]){
            printf("%d is Primzahl\n", i);
        }

        for(int j = i+i; j < n; j += i){
            prim[j] = false;
        }
    }    

    exit(EXIT_SUCCESS);
}
