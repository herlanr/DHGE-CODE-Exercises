// Template-Funktion: Anzahl und Wert des häufigsten Elementes eines Arrays
//
// Aufruf: haeufigstes worte ...
//
// Klaus Kusche, 2014

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

template <class T>
T haeufigstes(const T daten[], int anz, T nullWert, int &maxAnz)
{
  maxAnz = 0;
  T ergeb = nullWert;

  for (int i = 0; i < anz; ++i) {
    int anzahl = 1;   // 1 für das aktuelle Element
    for (int j = i + 1; j < anz; ++j) { // es reicht, die dahinter zu zählen
      if (daten[i] == daten[j]) {
        ++anzahl;
      }
    }
    if (anzahl > maxAnz) {
      ergeb = daten[i];
      maxAnz = anzahl;
    }
  }

  return ergeb;
}

int main(int argc, const char *argv[])
{
  int anz = argc - 1;
  string *worte = new string[anz];
  int *laengen = new int[anz];

  for (int i = 0; i < anz; ++i) {
    worte[i] = argv[i + 1];
    laengen[i] = strlen(argv[i + 1]);
  }
  
  int maxAnz;

  // Hier haben wir einen vom Compiler nicht auflösbaren Template-Aufruf:
  // Für den ersten Parameter müsste T gleich string sein,
  // für den dritten Parameter müsste T gleich char * sein
  //maxWort = haeufigstes(worte, anz, "", maxAnz);
  // Es gibt mindestens 4 Lösungsmöglichkeiten:
  // 1. Template-Typ explizit festlegen
  //    (dann konvertiert der Compiler das "" automatisch auf string)
  // 2. Dafür sorgen, dass der dritte Parameter Typ string hat
  //    (dann instanziert der Compiler das Template automatisch mit T=string):
  // 2a Explizite Typumwandlung von "" auf string
  // 2b string() als 3. Parameter (Standard-Konstruktor, liefert leeren String)
  // 2c Hilfsvariable vom Typ string, initialisiert mit "".
  string maxWort = haeufigstes<string>(worte, anz, "", maxAnz);
  //maxWort = haeufigstes(worte, anz, string(""), maxAnz);
  cout << "Häufigstes Wort: \"" <<  maxWort
       << "\" (Anzahl: " << maxAnz << ")" << endl;
  int maxLen = haeufigstes(laengen, anz, 0, maxAnz);
  cout << "Häufigste Laenge: " <<  maxLen
       << " (Anzahl: " << maxAnz << ")" << endl;

  exit(EXIT_SUCCESS);
}