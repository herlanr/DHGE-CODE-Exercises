#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void insertAtBeginning(Node **head, int newData) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = *head;
    *head = newNode;
}

void append(Node **head, int newData) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *last = *head;
    newNode->data = newData;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = newNode;
}

void removeFirst(Node **head) {
    if (*head == NULL) {
        return;
    }

    Node *temp = *head;
    *head = (*head)->next;
    free(temp);
}

void insertAtPosition(Node **head, int position, int newData) {
    if (position < 0) {
        printf("Invalid position\n");
        return;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = newData;

    if (position == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node *current = *head;
    for (int i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Position out of bounds\n");
        free(newNode);
        return;
    }

    newNode->next = current->next;
    current->next = newNode;
}

int main() {
    Node *head = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    insertAtBeginning(&head, 0);
    insertAtPosition(&head, 2, 5);
    removeFirst(&head);


    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    // Free the allocated memory
    while (head != NULL) {
        Node *temp = head; 
        head = head->next;
        free(temp);
    }

    return 0;
}



