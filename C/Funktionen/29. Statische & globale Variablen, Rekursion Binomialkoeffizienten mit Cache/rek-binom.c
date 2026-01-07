#include <stdio.h>
#include <stdlib.h>

int binomCalc(unsigned int n, unsigned int k);

int count;

int main(int argc, const char *argv[]){

    if (argc != 3){
        fprintf(stderr, "Aufruf: %s n k", argv[0]);
        exit(EXIT_FAILURE);
    }

    unsigned int n = atoi(argv[1]);
    unsigned int k = atoi(argv[2]);

    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= i; ++j ) {
            printf("%d ", binomCalc(i, j));
        }
        putchar('\n');
    }

    printf("Count: %d", count);

    exit(EXIT_SUCCESS);
}

int binomCalc(unsigned int n, unsigned int k){

    ++count;

    static unsigned int values[35][35];

    if (n > 35){
        fprintf(stderr, "n kann nicht grosser als 35 sein");
        exit(EXIT_FAILURE);
    } else if (k > n){
        return 0;
    } else if (k == 0 || k == n){
        return 1;
    } else if(values[n][k] == 0){
        values[n][k] = binomCalc(n - 1, k - 1) + binomCalc(n - 1, k);
        return values[n][k];
    } else {
        return values[n][k];
    }

}

