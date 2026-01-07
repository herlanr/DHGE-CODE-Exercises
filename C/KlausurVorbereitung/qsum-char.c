//ASCII-WERTEN quersumme

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, const char *argv[]){

	if (argc > 2){
		fprintf(stderr, "Aufruf: %s char Zahl\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	int sum = 0;
	
	for (int i = 0; argv[1][i] != '\0'; ++i){
		sum += argv[1][i] - '0';
	}
	
	printf("Sum: %d", sum);
	
	exit(EXIT_SUCCESS);
}