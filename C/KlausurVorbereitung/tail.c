#include <stdio.h>
#include <stdlib.h>

// Definition der Knotenstruktur
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Funktion zur Erstellung eines neuen Knotens
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Funktion zum Anhängen eines Knotens an das Ende der Liste
void append(Node** head, Node** tail, int data) {
    Node* newNode = createNode(data);
    if (*tail == NULL) {
        // Wenn die Liste leer ist, zeigen sowohl Head als auch Tail auf den neuen Knoten
        *head = newNode;
        *tail = newNode;
    } else {
        // Andernfalls wird der neue Knoten am Ende hinzugefügt und Tail aktualisiert
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

// Funktion zum Drucken der verketteten Liste
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;  // Initialisierung des Head-Pointers
    Node* tail = NULL;  // Initialisierung des Tail-Pointers

    append(&head, &tail, 1);
    append(&head, &tail, 2);
    append(&head, &tail, 3);
    append(&head, &tail, 4);

    printList(head);

    // Speicher freigeben (nicht gezeigt für Einfachheit)
    return 0;
}
