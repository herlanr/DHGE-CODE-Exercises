//vertausch von werten

#include <stdio.h>
#include <stdlib.h>
    
    int main(void){

		int number1 = 5;
		int number2 = 10;
		int temp;
		
		temp = number1;
		number1 = number2;
		number2 = temp;
		
		printf("number 1 : %d\n", number1);
		printf("number 2 : %d", number2);
		
		exit(EXIT_SUCCESS);
	}