//restrechnung und teilbarkeit
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

	int n = atoi(argv[1]);
	
	int sum = 0;
	
	while(n != 0){
		sum += n % 10;
		n /= 10;
	}
	
	printf("Sum: %d", sum);
	
	exit(EXIT_SUCCESS);
	
}