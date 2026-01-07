#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int strtolNew(const char *src, const char **zeichen);

int main(int argc, const char *argv[]) {

    if (argc == 1) {
        fprintf(stderr, "Aufruf: %s zahl1 zahl2 ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; ++i) {
        const char *ende;
        printf("%s = %d", argv[i], strtolNew(argv[i], &ende));
        if (*ende != '\0') {
            printf(", Rest des Wortes: \"%s\"\n", ende);
        } else {
            printf("\n");
        }
    }

    exit(EXIT_SUCCESS);
}

int strtolNew(const char *src, const char **zeichen) {

    int ergebnis = 0;

    for (; *src != '\0'; ++src) {
        if (isdigit(*src)) {
            ergebnis = ergebnis * 10 + (*src - '0');
        } else {
            break;  
        }
    }

    if (zeichen != NULL) {
        *zeichen = src; 
    }

    return ergebnis;
}
