#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){

    int number = abs(atoi(argv[1]));
    int sum = 0;

    while (number != 0){
        int lastDigit = number % 10;
        sum += lastDigit;

        number /= 10;
    }

    if (argc == 1){
        printf("%s", argv[0]);
    }

    printf("%d", sum);

    return 0;
}