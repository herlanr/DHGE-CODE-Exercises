#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *strrepeat(char *dest, char c, int cnt);

char *strtextcpy(char *dest, const char *src);

char *strappend(const char *src, char *dest);

int main(int argc, const char *argv[]){

    char result[] = {"Herlan Rodrigo"};
    const char result2[] = {"Ribeiro Rocha"};

    printf("strappend: %s", strappend(result2, result));

    exit(EXIT_SUCCESS);
}

//without malloc (Memory Allocation), using only pointers and pointers arithmetic
char *strappend(const char *src, char *dest){

    char *destPtr = dest;
    
    // Avança o ponteiro destPtr até o final da string dest
    while (*destPtr != '\0') {
        ++destPtr;
    }
    
    // Adiciona um espaço antes de concatenar a nova string
    *destPtr = ' ';
    ++destPtr;  // Avança para a posição após o espaço

    // Copia a string src para o final de dest
    while (*src != '\0') {
        *destPtr = *src;
        ++src;
        ++destPtr;
    }

    // Adiciona o terminador de string
    *destPtr = '\0';

    return dest;

}

char *strtextcpy(char *dest, const char *src){

    //*destP - Zeiger Deklaration - Zeiger auf das erste Element von (dest)
    char *destP = dest;

    //*src - Deserialization. überprüfen ob wir am Ende des Arrays (src) sind.
    //++src und ++destP sind Pointer Arithmetik
    for( ; *src != '\0'; ++src, ++destP){

        if (isspace(*src)){
            continue;
        } else{
            *destP = *src;
        }
    }

    *destP = '\0';

    return dest;

}


char *strrepeat(char *dest, char c, int cnt){

    //Zeiger Arithmetik
    //dest = zeiger auf das erstes element
    //cnt = count, wie viele char werden auf (dest) hinzugefügt
    //*destEnd = zeiger deklaration, zeiger auf das letztes element
    char *destEnd = dest + cnt;

    //*destPostion = zeiger auf die erste Position
    //*destPosition = c; Zeiger Deserialization, der Wert des Zeiger, wird mit (c) zugewiesen.
    for (char *destPosition = dest; destPosition <= destEnd; ++destPosition){
        *destPosition = c;
    }

    return dest;
}


