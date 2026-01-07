#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double wurzel(double number);

int main(int argc, const char *argv[]){

	if (argc != 2){
		fprintf(stderr, "Aufruf : %s", argv[0]);
		exit(EXIT_FAILURE);
	}

	double number = atof(argv[1]);
	double result = wurzel(number);
	double compareNumber = sqrt(number);
	
	printf("Naehrungsverfahren: %g\n", result);
	printf("Sqrt Funktion: %g\n", compareNumber);
	
	exit(EXIT_SUCCESS);

}

double wurzel(double number){

	double naherung = number;
	
	do{
	
		naherung = (naherung + number / naherung) / 2;
		
	} while(fabs(naherung * naherung - number) > number * 1e-10);
	
	return naherung;
	
}