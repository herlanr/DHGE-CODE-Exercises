#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    int aktuell = 0;
    int count = 0;
    int versuchen = 0;

    srand(time(0));

    while(count != 2){

        aktuell = rand() % 6 + 1;
        versuchen++;

        printf("%d ", aktuell);

        if (aktuell == 6){
            count++;
        } else {
            count = 0;
        }

    }

    printf("Zwei Sechser aufeinander!\n");
    printf("Versuchen: %d", versuchen);

    exit(EXIT_SUCCESS);
}