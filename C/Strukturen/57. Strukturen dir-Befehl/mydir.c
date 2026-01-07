#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

void errMsg(const char *operationName);

const char *progName;

const char *dirName;

//struct stat {
//    size_t st_size;
//    int st_mode;
//    time_t st_mtime;
//};

int main(int argc, const char *argv[]){

    progName = argv[0];

    DIR *dir;

    if((dir = opendir(".")) == NULL){
        errMsg("Cannot open the directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *dirRead = readdir(dir);

    struct stat info;

    while((dirRead = readdir(dir)) != NULL){
        errno = 0;
        printf("%s\n", dirRead->d_name);
        stat(dirRead->d_name, &info);
        printf("%ld", info.st_size);
    }

    if(dirRead == NULL){
        errMsg("Cannot read the directories");
    }

    exit(EXIT_SUCCESS);
}

void errMsg(const char *operationName){

    fprintf(stderr, "%s: error %s: %s", progName, operationName, strerror(errno));
    exit(EXIT_FAILURE);

}