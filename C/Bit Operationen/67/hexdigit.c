#include <stdio.h>
#include <stdlib.h>

int hexdigit(unsigned int z, unsigned int n){

    unsigned int hex = z;

    int ziffer = 0;

    while(hex != 0){
        ++ziffer;
        hex /= 10;
    }

    int verschiebung = (ziffer - n) << 2;

    return (z >> verschiebung) & 0xf;
    
}

int main(int argc, const char *argv[]){

    int z = strtoul(argv[1], NULL, 0);
    int n = atoi(argv[2]);

    printf("%08x --> %d", z, hexdigit(z, n));


    exit(EXIT_SUCCESS);
}
