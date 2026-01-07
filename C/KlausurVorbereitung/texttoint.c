#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int stringToInt(char const *zahl);

int main(int argc, const char *argv[]){

	if (argc == 1){
		fprintf(stderr, "Aufruf: %s zahl1 zahl2 ...", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	for(int i = 1; i < argc; ++i){
		printf("%s = %d", argv[i], stringToInt(argv[i]));		
	}
	
	exit(EXIT_SUCCESS);
}

int stringToInt(char const *zahl){

	int ergebnis = 0;
	
	for(int i = 0; zahl[i] != '\0'; ++i){
		
		if(isdigit(zahl[i])){
			ergebnis = ergebnis * 10 + zahl[i] - '0';
		} else {
            printf("'%c' ist keine Ziffer\n", zahl[i]);
            break;
        }
	}
	
	return ergebnis;
}