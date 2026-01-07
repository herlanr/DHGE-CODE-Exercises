#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char *argv[]){

    char zeichen;
    double number;
    double ergebnis = atof(argv[1]);

    for(int i = 2; i < argc; i++){

        number = atof(argv[i+1]);

        //argv[i][0] -- não precisa de de
        switch (argv[i][0]){          
            case '+':
                ergebnis = ergebnis + number;
                break;
            case '-':
                ergebnis = ergebnis - number;
                break;
            case 'x':
                ergebnis = ergebnis * number;
                break;
            case '/':
                ergebnis = ergebnis / number;
                break;
            case 'p':
                ergebnis = pow(ergebnis, number);
                break;            
            default:
                break;
        }
    }

    printf("Ergebnis: %g\n", ergebnis);
    

    exit(EXIT_FAILURE);
}