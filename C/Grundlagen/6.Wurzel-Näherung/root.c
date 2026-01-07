#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double root(double number);

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        printf("Fehler: Bitte geben Sie eine Zahl ein.\n");
        return 1;
    }

    double number = atof(argv[1]);

    if (number <= 0) {
        printf("Fehler: Bitte geben Sie eine positive Zahl ein.\n");
        return 1;
    }

    double result = root(number);

    printf("root: %.15f\n", result);

    return 0;
}

double root(double number) {
    
    double root = number;

    do {
        root = (root + number / root) / 2;
    } while (fabs(root * root - number) > number * 1e-10);

    return root;
}
