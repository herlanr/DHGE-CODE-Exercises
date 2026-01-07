//min und max
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

	if (argc == 1){
		fprintf(stderr, "Aufruf: %s zahl1 zahl2 ...\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	int min, max;
	min = max = atoi(argv[1]);
    int n;


	for(int i = 1; i < argc; ++i){
		
        n = atoi(argv[i]);

		if (n < min){
			min = n;
		} else if (n > max){
			max = n;
		}
	}
	
	printf("Max : %d\n", max);
	printf("Min : %d", min);
	
}