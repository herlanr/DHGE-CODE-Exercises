#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int stringToInt(const char string[]);

void intToString(char string[], int size, int number);

int main(int argc, const char *argv[]){

    int number = stringToInt(argv[1]);

    char string[12] = "+++++++++++";
    
    intToString(string, 12, number);

    printf("Befehlszeilen-Wort: %s\nUmgewandelten int: %d\nUmgewandelten string: %s", 
    argv[1], number, string);

    exit(EXIT_SUCCESS);
}

int stringToInt(const char string[]){

    char zeichen;
    int ergebnis = 0;

    for (int i = 0; (zeichen = string[i]) != '\0'; ++i){

        if (isdigit(zeichen)){  
            ergebnis = ergebnis * 10;
            ergebnis += zeichen - '0';
        } else {
            fprintf(stderr, "Fehlerhaften Zeichen (%c)", zeichen);
            return ergebnis;
        }
    }

    return ergebnis;
}

void intToString(char string[], int size, int number){

    int lastDigit = 0;
    string[size - 1] = '\0';

    int i;
    for(i = size - 2; number > 0; --i){

        lastDigit = number % 10;
        string[i] = lastDigit + '0';

        if (i < 0){
            fprintf(stderr, "Erfolglos Konvertierung");
            exit(EXIT_FAILURE);
        }

        number /= 10;
    }

    // i need the i outside the loop, because it has saved the position of the first
    // digit of the converted int. So that it possible to use (i) in this loop and change the
    // order of the string
    i++;
    for(int j = 0; i < size; ++j){
        string[j] = string[i];
        i++;
    }

}