#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

const char *progName;

const char *inFileName, *outFileName;

FILE *fIn, *fOut;

//fehler behebung für fopen, fclose, fwrite, argc != 3...
void errMsg(const char *operationName, const char *fileName);

int main(int argc, const char *argv[]){

    if (argc != 3){
        fprintf(stderr, "Aufruf: %s File1 File 2\n", progName);
        exit(EXIT_FAILURE);
    }

    progName = argv[0];
    inFileName = argv[1];
    outFileName = argv[2];

    if ((fIn = fopen(inFileName, "r")) == NULL){
        errMsg("Cannot open the file", inFileName);
    }

    if((fOut = fopen(outFileName, "w")) == NULL){
        errMsg("Cannot open the file", outFileName);
    }

    int c = fgetc(fIn);
    
    int spaces = 0;

    int leer = 0;

    while(c != EOF){

        if (isspace(c)){
            if (leer == 0){
                fputc(c, fOut);
                leer++;
            } else{
                spaces++;
            }
        } else{
            fputc(c, fOut);
            leer = 0;
        }
        
        c = fgetc(fIn);
    }

    if (fclose(fIn) == EOF){
        errMsg("Cannot close the file", inFileName);
    }

    if (fclose(fOut) == EOF){
        errMsg("Cannot close the file", outFileName);
    }

    printf("Total spaces: %d", spaces);

    exit(EXIT_SUCCESS);
}

void errMsg(const char *operationName, const char *fileName){

    fprintf(stderr, "%s: error %s %s: %s", progName, operationName, fileName, strerror(errno));
    exit(EXIT_FAILURE);

}