#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {

    // Überprüfung der Argumentanzahl
    if (argc != 3) {
        printf("Aufruf: %s basis exponent\n", argv[0]);
        return 1;
    }

    // Basis und Exponent einlesen
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
    double total = 1;

    // Sonderfälle behandeln
    if (base == 0 && exponent <= 0) {
        printf("Undefiniert: 0 hoch 0 oder 0 hoch negative Zahl\n");
        return 1;
    }
    if (exponent == 0) {
        total = 1;
    } else if (exponent < 0) {
        double inv_base = 1 / base;
        for (int i = exponent; i < 0; i++) {
            total *= inv_base;
        }
    } else {
        for (int i = exponent; i > 0; i--) {
            total *= base;
        }
    }

    // Ergebnis ausgeben
    printf("%.2f hoch %d = %.2f\n", base, exponent, total);

    return 0;
}
