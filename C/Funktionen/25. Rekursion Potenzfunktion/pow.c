#include <stdio.h>
#include <stdlib.h>

double hoch(double a, int n);

int main(int argc, const char *argv[]){

    if (argc != 3){
        fprintf(stderr, "Aufruf: %s a n", argv[0]);
        exit(EXIT_FAILURE);
    }

    double a = atof(argv[1]);
    int n = atoi(argv[2]);

    printf("%g hoch %d ist %g", a, n, hoch(a, n));

    exit(EXIT_SUCCESS);
    
}

double hoch(double a, int n){

    if(n == 0){
        return 1.0;
    } else if(n < 0){
        return 1 / hoch(a, -n);
    } else if((n % 2) == 0){
        return hoch(a*a, n/2);
    } else{
        return a * hoch(a, n-1);
    }

}