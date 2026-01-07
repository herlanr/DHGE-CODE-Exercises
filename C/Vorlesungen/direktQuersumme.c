#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

	if (argc != 2){
		fprintf(stderr, "Aufruf : %s", argv[0]);
		exit(EXIT_FAILURE);
	}

	const char *numbers = argv[1];
	int result = 0;
	
	for (int i = 0; numbers[i] != '\0'; i++){

		int value = numbers[i] - '0';
		result += value;
	}
	
	printf("Quersumme: %d", result);

	exit(EXIT_SUCCESS);

}
