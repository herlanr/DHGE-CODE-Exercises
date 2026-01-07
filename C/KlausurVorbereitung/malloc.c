#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição de uma struct
typedef struct {
    char *nome;
    int idade;
} Pessoa;

int main() {
    // 🔹 1. Alocação dinâmica de um ARRAY de inteiros
    int *array = (int *) malloc(5 * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Erro ao alocar memória para array\n");
        exit(EXIT_FAILURE);
    }

    // Inicializando e imprimindo os valores do array
    for (int i = 0; i < 5; i++) {
        array[i] = i * 10; // Exemplo: 0, 10, 20, 30, 40
        printf("array[%d] = %d\n", i, array[i]);
    }

    // 🔹 2. Alocação dinâmica de STRING usando malloc
    char *mensagem = (char *) malloc(20 * sizeof(char)); // Espaço para 19 caracteres + '\0'
    if (mensagem == NULL) {
        fprintf(stderr, "Erro ao alocar memória para string\n");
        free(array); // Libera memória antes de sair
        exit(EXIT_FAILURE);
    }
    strcpy(mensagem, "Hello, malloc!");
    printf("Mensagem: %s\n", mensagem);

    // 🔹 3. Alocação dinâmica de STRING usando strdup (copia automática)
    char *copia = strdup(mensagem);
    if (copia == NULL) {
        fprintf(stderr, "Erro ao alocar memória com strdup\n");
        free(array);
        free(mensagem);
        exit(EXIT_FAILURE);
    }
    printf("Cópia: %s\n", copia);

    // 🔹 4. Alocação dinâmica de uma STRUCT
    Pessoa *pessoa = (Pessoa *) malloc(sizeof(Pessoa));
    if (pessoa == NULL) {
        fprintf(stderr, "Erro ao alocar memória para struct Pessoa\n");
        free(array);
        free(mensagem);
        free(copia);
        exit(EXIT_FAILURE);
    }

    // 🔹 5. Alocação dinâmica de uma STRING dentro da struct
    pessoa->nome = (char *) malloc(30 * sizeof(char)); // Espaço para 29 caracteres + '\0'
    if (pessoa->nome == NULL) {
        fprintf(stderr, "Erro ao alocar memória para nome dentro da struct\n");
        free(array);
        free(mensagem);
        free(copia);
        free(pessoa); // Libera struct antes de sair
        exit(EXIT_FAILURE);
    }
    strcpy(pessoa->nome, "Alice");
    pessoa->idade = 25;

    printf("Pessoa: Nome = %s, Idade = %d\n", pessoa->nome, pessoa->idade);

    // 🔹 6. Liberação de memória (IMPORTANTE)
    free(array);
    free(mensagem);
    free(copia);
    free(pessoa->nome);
    free(pessoa);

    return 0;
}
