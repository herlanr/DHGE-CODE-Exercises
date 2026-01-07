#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strrepeat(char c, int cnt);

char *strtextcpy(const char *src);

int main(){

    printf("strrepeat: %s\n", strrepeat('A', 5));

    const char *src = {"DHGE"};

    printf("strtextcpy: %s", strtextcpy(src));

    exit(EXIT_SUCCESS);
}

char *strrepeat(char c, int cnt){

    char *dest = (char *) malloc(cnt+1);

    if (dest == NULL){
        fprintf(stderr, "Lack of memory");
        exit(EXIT_FAILURE);
    }

    char *destEnd = dest + cnt;

    for(char *destPosition = dest; destPosition < destEnd; ++destPosition){
        *destPosition = c;
    }

    *destEnd = '\0';

    return dest;
}

char *strtextcpy(const char *src){

    char *dest = (char *) malloc(strlen(src) + 1);

    char *destP = dest;
    
    for( ;*src != '\0'; ++src, ++destP){
        *destP = *src;
    }

    *destP = '\0';

    return dest;
}
