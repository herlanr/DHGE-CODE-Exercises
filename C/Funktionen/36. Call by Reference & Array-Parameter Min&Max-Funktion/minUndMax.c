#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool minUndMax(double values[], int size, double *max, double *min);

int main(int argc, const char *argv[]){

    double values[argc-1];
    double min, max;

    for(int i = 0; i < argc; ++i){
        values[i] = atof(argv[i+1]);
    }

    minUndMax(values, argc-1, &max, &min);

    exit(EXIT_SUCCESS);
}

bool minUndMax(double values[], int size, double *max, double *min){

    *max = *min = values[0];

    if (size < 1){
        fprintf(stderr, "Keine Argumente");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < size; ++i){

        if (values[i] > *max ){
            *max = values[i];
        }

        if (values[i] < *min ){
            *min = values[i];
        }
    }


    printf("Max: %g\n", *max);
    printf("Min: %g", *min);

    return true;

}