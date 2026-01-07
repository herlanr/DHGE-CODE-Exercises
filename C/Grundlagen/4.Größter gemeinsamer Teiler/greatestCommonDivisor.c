#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int gcd = 0;

    while(b > 0){

        int rest = abs(a % b);

        a = b;
        b = rest;
    }

    printf("gcd: %d", a);

    return 0;
}