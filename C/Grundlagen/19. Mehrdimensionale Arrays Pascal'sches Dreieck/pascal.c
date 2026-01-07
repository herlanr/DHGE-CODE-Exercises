#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

    int n = atoi(argv[1]) - 1;

    if(n < 0){
        fprintf(stderr, "%s: Ungultiges Zeilenzahl", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(argc != 2){
        fprintf(stderr, "Aufruf: %s Zeilenzahl<n>", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pascal[n][n];     


    //die erste zeile ab Spalte 1 gleich 0 einsetzen
    for(int s = 0; s < n; s++){
        pascal[0][s] = 0;
    }

    //die 0.Spalte als 1 einsetzen
    for(int z = 0; z < n; z++){
        pascal[z][0] = 1;
    }

    //die Tabelle ausfullen
    for(int z = 1; z < n; z++){
        for(int s = 1; s < n; s++){
            pascal[z][s] = pascal[z-1][s-1] + pascal[z-1][s];
        }
    }


    //ausgeben
    for (int z = 0; z < n; ++z) {
        for (int s = 0; s <= z; ++s) {
            printf("%5d ", pascal[z][s]);
        }

    }  

    exit(EXIT_SUCCESS);
}