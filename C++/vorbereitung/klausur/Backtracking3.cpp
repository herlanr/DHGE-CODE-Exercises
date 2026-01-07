// Rucksack packen, Optimierung mit Sortieren und Restgewicht
//
// Aufruf: rucksack Maximalgewicht
//
// Klaus Kusche, 2013

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Typ für die Daten eines Gegenstandes
typedef struct {
  char name[32];             // Bei Längenänderung: fscanf-Format anpassen!
  double gewicht;
  double wert;
  // Die Member akt_dabei (für die aktuelle Lösung)
  // und opt_dabei (für die optimale Lösung) zeigen an,
  // ob der Gegenstand eingepackt wird:
  // false ... Gegenstand i bleibt heraußen
  // true  ... Gegenstand i kommt in den Rucksack
  bool akt_dabei;
  bool opt_dabei;
  double faktor;             // Wert / Gewicht, für die Optimierung
} gegenstand;

// Liste aller Gegenstände
// Letztes Member faktor bleibt uninitialisiert, wird im Hauptprogramm berechnet
gegenstand liste[] = {
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

// Anzahl der Gegenstände in liste
const int anzahl = sizeof(liste) / sizeof(liste[0]);

// Wert der bisher besten Lösung (Summe aller Gegenstände mit opt_dabei)
double opt_wert = 0;

int aufruf = 0;              // Aufruf-Zähler

int vergleich(const void *p1, const void *p2);
void lsg(double wert);
void probier(int i, double platz, double wert);

// Die Vergleichsfunktion für qsort:
// Sortierung der Strukturen im Array nach dem member faktor
// Elemente mit *kleinerem* Wert pro Gewicht gehören
// beim Sortieren im Array nach *hinten*, sind also sortiermäßig *größer*!
int vergleich(const void *p1, const void *p2)
{
  const gegenstand *a = (const gegenstand *)p1;
  const gegenstand *b = (const gegenstand *)p2;

  if (a->faktor < b->faktor) {
    return 1;
  }
  if (a->faktor > b->faktor) {
    return -1;
  }
  return 0;
}

// akt_dabei enthält eine fertige Lösung, "wert" ist ihr gesamter Wert.
// Wenn sie besser ist als die bisher beste Lösung, 
// dann kopiere sie nach opt_dabei und merk dir den neuen optimalen Wert.
void lsg(double wert)
{
  if (wert > opt_wert) {
    for (int i = 0; i < anzahl; ++i) {
      liste[i].opt_dabei = liste[i].akt_dabei;
    }
    opt_wert = wert;
  }
}

// Probiere den Gegenstand Nummer i
// platz ist der noch freie Platz im Rucksack
// wert ist der bisherige Wert des Rucksacks
void probier(int i, double platz, double wert)
{
  ++aufruf;
  if (i == anzahl) {
    // kein Gegenstand mehr zur Wahl ==> Lösung ist fertig!
    lsg(wert);
    return;
  }
  
  gegenstand *g = &(liste[i]);   // Zeiger auf Gegenstand Nummer i
  
  // Optimierung:
  // Alle noch vorhandenen Gegenstände haben wegen der Sortierung
  // kleinergleich g->faktor Wert pro Gewicht.
  // Selbst wenn sie den noch vorhandenen Platz restlos füllen,
  // ist ihr Gesamtwert daher sicher kleinergleich (platz * g->faktor).
  // Wenn das in Summe weniger als die beste bekannte Lösung ist,
  // kann die aktuelle Lösung keine optimale mehr werden.
  if (wert + platz * g->faktor <= opt_wert) {
    return;
  }

  if (g->gewicht <= platz) {
    // Gegenstand hat noch Platz ==> probiere es mit ihm
    g->akt_dabei = true;
    probier(i + 1, platz - g->gewicht, wert + g->wert);
  }
  
  // probiere es in jedem Fall ohne den Gegenstand
  g->akt_dabei = false;
  probier(i + 1, platz, wert);
}

int main(int argc, const char *argv[])
{
  double platz;                 // Eingabe: Maximalgewicht des Rucksacks
  if ((argc != 2) || ((platz = atof(argv[1])) <= 0)) {
    fprintf(stderr, "Usage: %s max_gewicht\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  /*** Faktor berechnen ***/
  for (int i = 0; i < anzahl; ++i) {
    liste[i].faktor = liste[i].wert / liste[i].gewicht;
  }
  /*** Sortierung ***/
  qsort(liste, anzahl, sizeof(gegenstand), vergleich);

  /*** Berechnung ***/
  probier(0, platz, 0);

  /*** Ausgabe ***/
  double ges_gew = 0; // Gesamtgewicht der Lösung
  for (int i = 0; i < anzahl; ++i) {
    if (liste[i].opt_dabei) {
      printf("%-31s: Gewicht %9.2f, Wert %9.2f\n", liste[i].name,
             liste[i].gewicht, liste[i].wert);
      ges_gew += liste[i].gewicht;
    }
  }
  printf("%-31s: Gewicht %9.2f, Wert %9.2f\n", "Summe", ges_gew, opt_wert);
  printf("Anzahl der Aufrufe: %d\n", aufruf);
  
  exit(EXIT_SUCCESS);
}