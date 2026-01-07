#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

	if(argc == 1){
		printf("Eingabefehler: %s", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	int max = atoi(argv[1]);
	int min = atoi(argv[1]);
	
	for(int i = 1; i < argc; i++){
	
		int number = atoi(argv[i]);
		
		if(number > max){
			max = number;
		} else if (number < min){
			min = number;
		} else {
			continue;
		}
	
	}
	
	printf("Max : %d", max);
	printf("Min : %d", min);
	
	exit(EXIT_SUCCESS);
	
}
		