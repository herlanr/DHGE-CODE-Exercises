#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void balken(int kugelImFaecher[], int faecherZahl) {
    for (int i = 0; i < faecherZahl + 1; i++) {
        printf("Fächer %d sind: %d Kugel\n", i, kugelImFaecher[i]);
    }
}

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <kugelZahl> <reihenZahl>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int kugelZahl = atoi(argv[1]);
    int reihenZahl = atoi(argv[2]);
    int faecherZahl = reihenZahl; // Number of bins equals number of rows
    int kugelImFaecher[faecherZahl + 1];

    // Initialize the array to 0
    for (int i = 0; i < faecherZahl + 1; i++) {
        kugelImFaecher[i] = 0;
    }

    srand(time(0)); // Seed the random number generator

    // Simulate each ball
    for (int i = 0; i < kugelZahl; i++) {
        int fach = faecherZahl / 2; // Start in the middle

        // Simulate the ball's path
        for (int j = 0; j < reihenZahl; j++) {
            int richtung = rand() % 2; // Random direction (0 or 1)
            if (richtung == 1 && fach < faecherZahl) {
                fach++; // Move right
            } else if (richtung == 0 && fach > 0) {
                fach--; // Move left
            }
        }

        // Increment the count for the final position
        kugelImFaecher[fach]++;
    }

    // Print the result
    balken(kugelImFaecher, faecherZahl);

    return EXIT_SUCCESS;
}
