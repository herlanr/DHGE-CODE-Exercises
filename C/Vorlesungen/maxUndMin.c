#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, const char *argv[]){

	if (argc == 1){
		fprintf(stderr, "Aufruf : %s", argv[0]);
		exit(EXIT_FAILURE);
	}

	int max = atoi(argv[1]);
	int min = max;


	
	for(int i = 1; i < argc; i++){
	
        int number = atoi(argv[i]);

        if(!isdigit(*argv[i])){
		    fprintf(stderr, "Aufruf: %s", argv[0]);
            exit(EXIT_FAILURE);
        }

		if (number > max){
			max = number;
		} else if (number < min){
			min = number;
		}
	}
	
	printf("Min: %d\n", min);
	printf("Max: %d", max);
	
	exit(EXIT_SUCCESS);
}