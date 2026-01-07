#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {

    int dezimal = 0;

    for (int i = 1; i < argc; i++) {

        dezimal = 0;  

        for (int j = 0; argv[i][j] != '\0'; j++) {

            char c = argv[i][j];

            switch (c) {
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                    dezimal = dezimal * 16 + (c - '0');
                    break;
                case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
                    dezimal = dezimal * 16 + (c - 'A' + 10);
                    break;
                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                    dezimal = dezimal * 16 + (c - 'a' + 10);
                    break;
                default:
                    fprintf(stderr, "Eingabe Fehler: %c\n", c);
                    exit(EXIT_FAILURE);
            }
        }

        printf("%s = %d\n", argv[i], dezimal);
    }

    exit(EXIT_SUCCESS);
}
