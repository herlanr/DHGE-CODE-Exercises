#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(){

    const int ZAHLEN = 49;
    const int KUGELN = 6;
    bool values[ZAHLEN];

    // Der Array mit Werten ausfüllen
    for(int i = 0; i <= ZAHLEN; i++){
        values[i] = false;
    }

    srand(time(0));
    int number = 0;

    for(int i = 0; i <= KUGELN; i++){

        number = rand() % ZAHLEN;
        values[number] = true;

    }

    //print
    for (int i = 0; i <= ZAHLEN; i++){

        if (values[i]){
            printf("Zahl %d\n", i);
        }

    }

    return EXIT_SUCCESS;
}