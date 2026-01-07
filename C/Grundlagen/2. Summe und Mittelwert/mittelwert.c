#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, const char *argv[]){

    // = 0 nicht vergessen, sonst hat summe einen zufälligen Anfangswert!
    double summe = 0;

    if(argc == 1){
        printf("Hey, du solltest etwas eingeben! %s", argv[0]);
        return 1;
    } 

    for (int i = 1; i < argc; i++){
        summe += atof(argv[i]);
    }

    double mittelwert = summe / (argc - 1);

    printf("Die Summe lautet:      %16lf\n", summe);
    printf("Der Mittelwert lautet: %16lf", mittelwert);

    return 0;
}