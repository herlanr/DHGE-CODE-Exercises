#include <iostream>

using namespace std;

struct Item{
    char name[32];
    double gewicht;
    double wert;
    bool akt_dabei;
    bool opt_dabei;
};

Item items[] = {
    { "Apfel", 10, 5, false, false },
    { "Müsliriegel", 2.5, 25, false, false },
    { "Goldring", 0.5, 1666, false, false },
    { "Schleppdepp", 70, 499.99, false, false },
    { "Paß", 0.5, 60, false, false },
    { "Geldbörse", 5, 123.27, false, false },
    { "Kamera", 49.5, 459.99, false, false },
    { "Brille", 13, 260.50, false, false },
    { "Saft", 30, 30, false, false },
    { "Pullover", 12, 20, false, false },
    { "Regenmantel", 3.5, 40, false, false },
    { "Messer", 10, 50, false, false },
    { "Taschentuch", .1, .5, false, false },
    { "Klopapier", 0.5, 5, false, false },
    { "Banane", 5, 10, false, false },
    { "Karte", 1.5, 20, false, false },
    { "Sonnencreme", 7.5, 40, false, false }
};

const int anzahl = sizeof(items) / sizeof(items[0]); 

double opt_wert = 0;

int aufruf = 0;              

void saveSolution(double totalWert){
    if (totalWert > opt_wert){
        opt_wert = totalWert;
        for (int i = 0; i < anzahl; ++i) {
            items[i].opt_dabei = items[i].akt_dabei;
        }
    }
}

void probier(int index, double platz, double totalWert){
    
    ++aufruf;

    if(index == anzahl){
        saveSolution(totalWert);
        return;
    }

    Item &item = items[index];

    if(item.gewicht <= platz){
        item.akt_dabei = true;
        probier(index + 1, platz - item.gewicht, totalWert + item.wert);
    }

    item.akt_dabei = false;
    probier(index + 1, platz, totalWert);
}

int main(int argc, const char *argv[])
{
  double platz;                 // Eingabe: Maximalgewicht des Rucksacks
  if ((argc != 2) || ((platz = atof(argv[1])) <= 0)) {
    fprintf(stderr, "Usage: %s max_gewicht\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  /*** Berechnung ***/
  probier(0, platz, 0);

  /*** Ausgabe ***/
  double ges_gew = 0; // Gesamtgewicht der Lösung
  for (int i = 0; i < anzahl; ++i) {
    if (items[i].opt_dabei) {
      printf("%-31s: Gewicht %9.2f, Wert %9.2f\n", items[i].name,
             items[i].gewicht, items[i].wert);
      ges_gew += items[i].gewicht;
    }
  }
  printf("%-31s: Gewicht %9.2f, Wert %9.2f\n", "Summe", ges_gew, opt_wert);
  printf("Anzahl der Aufrufe: %d\n", aufruf);
  
  exit(EXIT_SUCCESS);
}


