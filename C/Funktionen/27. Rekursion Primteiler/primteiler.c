#include <stdio.h>
#include <stdlib.h>

void primfaktoren(int zahl, int teiler);

int main(int argc, const char *argv[]){

    if(argc != 2){
        fprintf(stderr, "Aufruf: %s zahl", argv[0]);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

void primfaktoren(int zahl, int teiler){    

    if(zahl >= teiler){
        
    }
}