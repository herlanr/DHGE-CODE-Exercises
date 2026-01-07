#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

FILE *fIn, *fOut;

const char *programName, *fInName, *fOutName;

void errMsg(const char *Msg, const char *fileName);

int main(int argc, const char *argv[]){

    programName = argv[0];
    fInName = argv[1];
    fOutName = argv[2];

    if(argc != 3){
        fprintf(stderr, "Aufruf: %s file1 file2", programName);
        exit(EXIT_FAILURE);
    }

    if((fIn = fopen(fInName, "r")) == NULL){
        errMsg("Cannot open the file", fInName);
    }

    if((fOut = fopen(fOutName, "w")) == NULL){
        errMsg("Cannot open the file", fOutName);
    }

    int c;

    while(c = fgetc(fIn) != EOF){
        fputc(c, fOut);
    }

    exit(EXIT_SUCCESS);
}

void errMsg(const char *msg, const char *fileName){

    fprintf(stderr, "%s: %s error %s: %s", programName, msg, fileName, strerror(errno));
    exit(EXIT_FAILURE);
}