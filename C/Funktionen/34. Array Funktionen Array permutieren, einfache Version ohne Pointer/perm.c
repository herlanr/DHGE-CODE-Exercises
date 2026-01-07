#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool perm(int values[], int size);

void swap(int values[], int n1, int n2);

void reverse(int values[], int n1, int n2);

int find_smaller(const int values[], int size);

int find_larger(const int values[], int size, int n);

void fill(int values[], int n);

void print(const int values[], int size);

int main(int argc, const char *argv[]){

    if (argc != 2){
        fprintf(stderr, "Aufruf: %s n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);

    if (n < 1 || n > 30){
        fprintf(stderr, "%s: Die Anzahl (%d) muss zwischen 1 und 30 sein!\n", argv[0], n);
        exit(EXIT_FAILURE);
    }

    int values[n];

    fill(values, n);

    print(values, n);

    while(perm(values, n)){

        print(values, n);
    }

    exit(EXIT_SUCCESS);

}

bool perm(int values[], int size){

    int links = find_smaller(values, size);

    if (links == -1){
        return false;
    }

    int rechts = find_larger(values, size, values[links]);

    swap(values, links, rechts);

    reverse(values, links+1, size-1);

    return true;

}

void swap(int values[], int n1, int n2){

    int t = values[n1];
    values[n1] = values[n2];
    values[n2] = t;

}

void reverse(int values[], int n1, int n2){

    for( ; n1 < n2; ++n1, --n2){
        swap(values, n1, n2);
    }
}

int find_smaller(const int values[], int size){

    for (int i = size-2; i >= 0; --i){

        if(values[i] < values[i+1]){
            return i;
        }
    }

    return -1;

}

int find_larger(const int values[], int size, int n){

    for(int i = size-1; i >= 0; --i){

        if(values[i] > n){
            return i;
        }
    }

    return -1;
}

void fill(int values[], int n){

    for (int i = 0; i < n; ++i){
        values[i] = i + 1;
    }

}

void print(const int values[], int size){

    for(int i = 0; i < size; ++i){
        printf("%d ", values[i]);
    }
    printf("\n");
}