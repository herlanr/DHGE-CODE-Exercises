//LESEN AUS BEFEHLZEILE

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

	if(argc == 1){
		fprintf(stderr, "Aufruf: %s double1 double2 ...", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	double sum = 0;
	
	for(int i = 1; i < argc; ++i){
		sum += atof(argv[i]);
	}
	
	printf("%g", sum);
	
	exit(EXIT_SUCCESS);

}