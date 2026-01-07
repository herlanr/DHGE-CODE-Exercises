#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *input = stdin;   // Arquivo de entrada padrão
    FILE *output = stdout;  // Arquivo de saída padrão

    // Se um nome de arquivo for fornecido como argumento, use ele
    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo %s para leitura: %s\n", argv[1], strerror(errno));
            return 1;
        }
    }

    // Se um segundo nome de arquivo for fornecido, use ele para saída
    if (argc > 2) {
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo %s para escrita: %s\n", argv[2], strerror(errno));
            return 1;
        }
    }

    char buffer[256];

    // Lê uma linha de input (pode ser stdin ou arquivo)
    while (fgets(buffer, sizeof(buffer), input) != NULL) {
        // Escreve a linha para output (pode ser stdout ou arquivo)
        fputs(buffer, output);
    }

    // Fechar os arquivos, se necessário
    if (input != stdin) {
        fclose(input);
    }
    if (output != stdout) {
        fclose(output);
    }

    return 0;
}
