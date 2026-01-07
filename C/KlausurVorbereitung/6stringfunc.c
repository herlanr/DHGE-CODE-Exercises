#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    char original[] = "Ola, mundo";
    char *copia = strdup(original);
    char destino[50];

    // Corrected: str1 should be a character array, not an array of pointers
    char str1[50] = "Ola";  
    char str2[] = "Herlan";

    // Concatenation (ensure enough space)
    strcat(str1, str2);

    // Fixed: String comparison
    const char *string1 = "apple";
    const char *string2 = "banana";
    int resultadoStrcmp = strcmp(string1, string2);

    // Fixed: String search
    char *resultadoStrstr = strstr(original, "O");

    // Fixed: Correct order in strcpy
    strcpy(destino, original);

    // Check memory allocation for strdup
    if (copia == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Corrected Print Statements
    printf("Original: %s\n", original);
    printf("Copia: %s\n", copia);
    printf("Strstr: %s\n", resultadoStrstr);
    printf("Strcpy: %s\n", destino);
    printf("Strcat: %s\n", str1);
    printf("Strcmp: %d\n", resultadoStrcmp);
    printf("Strlen: %lu\n", strlen(str2));

    // Free dynamically allocated memory
    free(copia);

    exit(EXIT_SUCCESS);
}
