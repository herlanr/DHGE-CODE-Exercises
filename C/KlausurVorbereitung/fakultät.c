//REKURSION

#include <stdio.h>
#include <stdlib.h>

int fak(int n);

int main(int argc, const char *argv[]){

	if(argc != 2){
		fprintf(stderr, "Aufruf: %s zahl\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	int n = atoi(argv[1]);
	
	printf("Fak: %d", fak(n));
	
	exit(EXIT_SUCCESS);
	
}

int fak(int n){

	if(n <= 1){
		return 1;
	}
	
	return n * fak(n - 1);
}