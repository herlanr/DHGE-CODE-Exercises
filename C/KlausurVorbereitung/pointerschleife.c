//array pointer schleife
#include <stdio.h>

int main(){

    char str[] = "Hello world";
    char *p = str;

    while (*p != '\0'){
        printf("%c", *p);
        ++p;
    }

    return 0;
}