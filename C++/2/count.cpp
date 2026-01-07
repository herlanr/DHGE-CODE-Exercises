#include <iostream>
#include <cstdlib>

using namespace std;

const int ARR_LENGTH = 10;

struct Element{
  int wert;
  int anzahl;
};

struct Daten{
  Element arr_elem[ARR_LENGTH];
  int elemente;
};

Element &suche(Daten &daten, int zahl);
void druck(Daten &daten);

int main(int argc, const char *argv[]){

  Daten daten;
  daten.elemente = 0;

  for(int i = 0; i < argc; i++){
    ++(suche(daten, atoi(argv[i])).anzahl);
  }

  druck(daten);
}

Element &suche(Daten &daten, int zahl){

  int i;

  for(i = 0; i < daten.elemente; i++){
    if (daten.arr_elem[i].wert == zahl){
      return daten.arr_elem[i];
    }
  }

  if (daten.elemente == ARR_LENGTH){
    cerr << "Zu viele Werte. Max: " << ARR_LENGTH << endl;
    exit(EXIT_FAILURE);
  }

  daten.arr_elem[i].wert = zahl;
  daten.arr_elem[i].anzahl = 0;
  daten.elemente++;
  return daten.arr_elem[i];
}

void druck(Daten &daten){
  for (int i = 0; i < daten.elemente; i++){
    cout << "Wert: " << daten.arr_elem[i].wert << " : " << daten.arr_elem[i].anzahl << " Stuck" << endl;
  }
}