#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura Pessoa
typedef struct Pessoa {
    char nome[100];
    int idade;
    float saldo;
    struct Pessoa* prox; // Ponteiro para o próximo nó
} Pessoa;

// Função para adicionar uma pessoa ao final da lista
void adicionar_pessoa(Pessoa **inicio, const char *nome, int idade, float saldo) {
    Pessoa *nova_pessoa = (Pessoa *) malloc(sizeof(Pessoa));
    if (nova_pessoa == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    // Inicializar a nova pessoa
    strncpy(nova_pessoa->nome, nome, sizeof(nova_pessoa->nome) - 1);
    nova_pessoa->nome[sizeof(nova_pessoa->nome) - 1] = '\0'; // Garantir que a string esteja terminada
    nova_pessoa->idade = idade;
    nova_pessoa->saldo = saldo;
    nova_pessoa->prox = NULL;

    // Adicionar ao final da lista
    if (*inicio == NULL) {
        *inicio = nova_pessoa;  // A lista estava vazia
    } else {
        Pessoa *temp = *inicio;
        while (temp->prox != NULL) {
            temp = temp->prox; // Encontrar o último nó
        }
        temp->prox = nova_pessoa; // Adicionar a nova pessoa
    }
}

// Função para imprimir todos os dados das pessoas na lista
void imprimir_lista(Pessoa *inicio) {
    if (inicio == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    Pessoa *temp = inicio;
    while (temp != NULL) {
        printf("Nome: %s, Idade: %d, Saldo: %.2f\n", temp->nome, temp->idade, temp->saldo);
        temp = temp->prox;
    }
}

// Função para liberar toda a memória da lista
void liberar_lista(Pessoa *inicio) {
    Pessoa *temp;
    while (inicio != NULL) {
        temp = inicio;
        inicio = inicio->prox;
        free(temp); // Liberar o nó atual
    }
}

// Função para ler pessoas de um arquivo e adicionar à lista
void ler_pessoas_de_arquivo(Pessoa **inicio, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char nome[100];
    int idade;
    float saldo;

    // Ler dados linha por linha e adicionar à lista
    while (fscanf(arquivo, "%99s %d %f", nome, &idade, &saldo) == 3) {
        adicionar_pessoa(inicio, nome, idade, saldo);
    }

    fclose(arquivo); // Fechar o arquivo
}

int main() {
    Pessoa *lista = NULL; // Lista vazia

    // Ler pessoas do arquivo e adicionar à lista
    ler_pessoas_de_arquivo(&lista, "pessoas.txt");

    // Imprimir todos os dados das pessoas na lista
    printf("Lista de pessoas:\n");
    imprimir_lista(lista);

    // Liberar a memória alocada pela lista
    liberar_lista(lista);

    return 0;
}
