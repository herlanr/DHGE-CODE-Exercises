#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *next;
} Node;

Node *createNode(int data){

	Node *newNode = (Node *) (malloc(sizeof(Node)));
	
	newNode->data = data;
	newNode->next = NULL;
	
	return newNode;
}

void printList(Node *node){

	Node *head = node;
	while(head != NULL){
	
		printf("%d", head->data);
		head = head->next;
	}

}

int main(){

    Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
	
	printList(head);

}