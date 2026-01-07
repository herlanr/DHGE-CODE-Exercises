//Gera e imprime um número aleatório entre 0 e 5.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

	srand(time(NULL));
	
	int n = rand() % 6;
	
	printf("%d", n);

	exit(EXIT_SUCCESS);
}