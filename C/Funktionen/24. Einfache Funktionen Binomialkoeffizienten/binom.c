#include <stdio.h>
#include <stdlib.h>

int binomCalc(int n, int k);

int fakCalc(int zahl);

int main(int argc, const char *argv[]){

    if (argc != 2){
        fprintf(stderr, "Aufruf : %s Zeilen", argv[0]);
        exit(EXIT_FAILURE);
    }

    int zeilen = atoi(argv[1]);

    for(int i = 0; i <= zeilen; i++){
        for(int j = 0; j <= i; ++j ) {
            printf("%d ", binomCalc(i, j));
        }
        putchar('\n');
    }

    exit(EXIT_SUCCESS);
}

int fakCalc(int zahl){

    int ergebnis = 1;

    for(int i = zahl; i > 1; i--){
        ergebnis *= i;
    }

    return ergebnis;

}

int binomCalc(int n, int k){

    int ergebnis = 0;
    int nFak = fakCalc(n);
    int kFak = fakCalc(k);
    int nMinkFak = fakCalc(n - k);

    ergebnis = nFak / (kFak * nMinkFak);

    return ergebnis;

}