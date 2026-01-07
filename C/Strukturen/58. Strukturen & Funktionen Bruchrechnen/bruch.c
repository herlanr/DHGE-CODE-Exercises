#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bruch {
    int zaehler;
    int nenner;
} Bruch;

struct Bruch addieren(Bruch zahl1, Bruch zahl2);

struct Bruch subtrahieren(Bruch zahl1, Bruch zahl2);

struct Bruch multiplizieren(Bruch zahl1, Bruch zahl2);

struct Bruch dividieren(Bruch zahl1, Bruch zahl2);

struct Bruch stringToBrunch(const char string[]);

void ergebnisAusgeben(Bruch ergebnis);

void kuerzer(Bruch *ergebnis);

int ggT(int n1, int n2);

int main(int argc, const char *argv[]){

    Bruch ergebnis = stringToBrunch(argv[1]);

    for(int i = 2; i < argc; i += 2){

        Bruch bruch2 = stringToBrunch(argv[i+1]);

        switch (argv[i][0])
        {
        case '+':
            ergebnis = addieren(ergebnis, bruch2);
            break;

        case '-':
            ergebnis = subtrahieren(ergebnis, bruch2);
            break;

        case '/':
            ergebnis = dividieren(ergebnis, bruch2);
            break;

        case '*':
            ergebnis = multiplizieren(ergebnis, bruch2);
            break;
        
        default:
            break;
        }

    }

    Bruch *ergebnisPtr = &ergebnis;

    kuerzer(ergebnisPtr);

    ergebnisAusgeben(ergebnis);

    exit(EXIT_SUCCESS);

}

struct Bruch addieren(Bruch zahl1, Bruch zahl2){

    Bruch ergebnis;

    ergebnis.zaehler = (zahl1.zaehler * zahl2.nenner + zahl2.zaehler * zahl1.nenner); 
    ergebnis.nenner = (zahl1.nenner * zahl2.nenner);

    return ergebnis;
}

struct Bruch subtrahieren(Bruch zahl1, Bruch zahl2){

    Bruch ergebnis;

    ergebnis.zaehler = (zahl1.zaehler * zahl2.nenner - zahl2.zaehler * zahl1.nenner); 
    ergebnis.nenner = (zahl1.nenner * zahl2.nenner); 

    return ergebnis;
}

struct Bruch multiplizieren(Bruch zahl1, Bruch zahl2){

    Bruch ergebnis;

    ergebnis.zaehler = (zahl1.zaehler * zahl2.zaehler); 
    ergebnis.nenner = (zahl1.nenner * zahl2.nenner); 

    return ergebnis;
}

struct Bruch dividieren(Bruch zahl1, Bruch zahl2){

    Bruch ergebnis;

    ergebnis.zaehler = (zahl1.zaehler * zahl2.nenner); 
    ergebnis.nenner = (zahl1.nenner * zahl2.zaehler); 

    return ergebnis;
}

void ergebnisAusgeben(Bruch ergebnis){
    
    if (ergebnis.nenner != 1){
        printf("Zaehler: %d\n", ergebnis.zaehler);
        printf("Nenner: %d", ergebnis.nenner);
    } else {
        printf("ganze Zahl: %d", ergebnis.zaehler);
    }

}

struct Bruch stringToBrunch(const char string[]){

    Bruch ergebnis;
    char *slash;

    if(slash = strchr(string, '/')){
        ergebnis.zaehler = atoi(string);
        ergebnis.nenner = atoi(slash + 1);
    } else {
        ergebnis.zaehler = atoi(string);
        ergebnis.nenner = 1;
    }

    return ergebnis;
    
}

void kuerzer(Bruch *ergebnis){

    if (ergebnis->nenner == 0){
        fprintf(stderr, "Fehler");
        exit(EXIT_FAILURE);
    }

    if (ergebnis->nenner < 0){
        ergebnis->zaehler = (-1) * ergebnis->zaehler;
        ergebnis->nenner = (-1) * ergebnis->nenner;
    }

    int ggtValue = ggT(ergebnis->zaehler, ergebnis->nenner);

    ergebnis->zaehler /= ggtValue;
    ergebnis->nenner /= ggtValue;

}

int ggT(int a, int b){

    int r;

    a = abs(a);
    b = abs(b);

    while(b != 0){
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}


