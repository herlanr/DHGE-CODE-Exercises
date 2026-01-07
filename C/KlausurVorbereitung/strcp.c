#include <stdio.h>

char *newStrcpy(char *dest, const char *src){

	char *destP = dest;
	const char *srcP = src;
	
	for( ; *srcP != '\0'; ++srcP, ++destP){
		
		*destP = *srcP;
	}
	
	++destP;
	*destP = '\0';
	
	return dest;
}

int main(){

    char example[] = {""};
    const char example2[] = {"Rocha"};

    newStrcpy(example, example2);

    printf("%s", example);

}