#include <stdio.h>
#include <string.h> // Necessário para strlen()

void splitInPlace(char *str) {
    char *p = str;
    
    while (*p) {
        if (*p == ' ') {
            *p = '\0'; // Substitui espaço por '\0' para dividir a string
        }
        p++;
    }
}

int main() {
    char text[] = "Hallo Welt das ist C"; // Importante: Usar array, não ponteiro constante
    
    splitInPlace(text); // Divide a string no próprio local

    // Percorre e imprime as partes da string separadas
    char *ptr = text;
    while (*ptr) {
        printf("%s\n", ptr);
        ptr += strlen(ptr) + 1; // Avança para o próximo pedaço
    }

    return 0;
}
z