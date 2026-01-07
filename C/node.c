#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do nó da lista
typedef struct Node {
    int data;               // Dado armazenado no nó
    struct Node* next;      // Ponteiro para o próximo nó
} Node;

// Função para criar um novo nó
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Aloca memória para o novo nó
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);  // Encerra o programa em caso de falha na alocação
    }
    newNode->data = value;  // Armazena o valor no nó
    newNode->next = NULL;    // Inicializa o ponteiro next com NULL (final da lista)
    return newNode;
}

// Função para adicionar um nó no final da lista (usando o tail pointer)
void append(Node** head, Node** tail, int value) {
    Node* newNode = createNode(value);  // Cria o novo nó
    if (*tail == NULL) {
        *head = *tail = newNode;  // Se a lista estiver vazia, head e tail apontam para o novo nó
    } else {
        (*tail)->next = newNode;  // Conecta o nó anterior (tail) ao novo nó
        *tail = newNode;          // Atualiza o tail para apontar para o novo nó
    }
}

// Função para imprimir a lista
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Função para liberar a memória da lista
void freeList(Node* head) {
    Node* current = head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;   // Guarda o próximo nó
        free(current);           // Libera a memória do nó atual
        current = next;          // Avança para o próximo nó
    }
}

int main() {
    Node* head = NULL;  // Cabeça da lista
    Node* tail = NULL;  // Tail da lista

    // Adicionando elementos à lista
    append(&head, &tail, 10);
    append(&head, &tail, 20);
    append(&head, &tail, 30);
    append(&head, &tail, 40);

    // Imprimindo a lista
    printf("Lista ligada: ");
    printList(head);

    // Liberando a memória da lista
    freeList(head);

    return 0;
}
