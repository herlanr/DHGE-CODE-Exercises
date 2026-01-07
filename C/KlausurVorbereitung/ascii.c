//ascii 

#include <stdio.h>

int main() {
    // 1. Converter um caractere para valor numérico
    char digito = '7';
    int valorNumerico = digito - '0';  // Subtraindo o valor ASCII de '0'

    printf("Caractere: %c, Valor numérico: %d\n", digito, valorNumerico);

    // 2. Converter um valor numérico para caractere
    int outroValorNumerico = 5;
    char outroDigito = outroValorNumerico + '0';  // Somando o valor ASCII de '0'

    printf("Valor numérico: %d, Caractere: %c\n", outroValorNumerico, outroDigito);

    return 0;
}
