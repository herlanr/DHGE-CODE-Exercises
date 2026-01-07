#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {

    if (argc != 2) {  
        printf("Eingabefehler: ", argv[0]);
        exit(EXIT_FAILURE); 
    }

    int summe = 0;
    const char *number = argv[1]; 

    for (int i = 0; number[i] != '\0'; i++) { 
        int digit = number[i] - '0';
        summe += digit;
    }
    
    printf("Summe : %d", summe);

    return 0;
}
