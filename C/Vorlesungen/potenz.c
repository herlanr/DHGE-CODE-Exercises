#include <stdio.h>
#include <stdlib.h>

double power(double basis, double expoent);

int main(int argc, const char *argv[]){

	if (argc != 3){
		fprintf(stderr, "Aufruf :%s", argv[0]);
		exit(EXIT_FAILURE);
	}

	double basis = atof(argv[1]);
	double expoent = atof(argv[2]);
	double result = power(basis, expoent);
	
	printf("%g hoch %g: %g", basis, expoent, result);
	
	exit(EXIT_SUCCESS);

}

double power(double basis, double expoent){

	double result = 1;

	if (expoent > 0){
	
		for(int i = 0; i != expoent; i++){
			
			result *= basis;
		}
	} else {
	
		for (int i = expoent; i != 0; i++){
			
			result = result * (1 / basis);
			
		}
	}
	
	return result;

}