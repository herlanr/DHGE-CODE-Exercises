#include <stdio.h>
#include <stdlib.h>

int querSumme(int number);

int main(int argc, const char *argv[]){

    int number = abs(atoi(argv[1]));

    int sum = querSumme(number);
    int ganzeSum = querSumme(sum);

    printf("The total Quersumme is: %d", ganzeSum);

    return 0;
}

int querSumme(int number){

    int sum = 0;

    while (number != 0){

        // % 10 the remainder is always the last digit
        int lastDigit = number % 10;
        sum += lastDigit;
        number /= 10;
    }

    return sum;
}