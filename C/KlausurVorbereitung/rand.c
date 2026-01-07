//STATIC VARIABLE AND ZUFALLSZAHLEN

#include <stdio.h>
#include <stdlib.h>

#define ANZAHL 30

int myRand(unsigned int from, unsigned int to);

int main(void){

	int n = 0;
	int sum = 0;

	for(int i = 0; i <= ANZAHL; ++i){
		n = myRand(1, 6);
		sum += n;
		printf("%d ", n);
	}
	
    double mittelwert = sum/ANZAHL;

	printf("Mittelwert: %f", mittelwert);
	
	exit(EXIT_SUCCESS);

}

int myRand(unsigned int from, unsigned int to){

	static unsigned int number = 1;
	
	number = number * 1103515245 + 12345;
	
	return number % (to - from + 1) + from;
	
}