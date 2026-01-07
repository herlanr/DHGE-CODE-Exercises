#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

    if (argc == 1){
        printf("Hello, ich bin %s, wer bist du?\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for(int i = argc - 1; i > 0; i--){

        if (i == argc -1){
            printf("Hallo, %s, du bist Erster\n", argv[i], i);
            continue;
        }

        printf("Hallo, %s, %d. Platz\n", argv[i], (i - argc) * -1);
    }

    if ((argc - 1) > 10){
        printf("Hallo an alle!");
    } else {
        printf("Ihr seid %d Leute.", argc -1);
    }

    exit(EXIT_SUCCESS);
}