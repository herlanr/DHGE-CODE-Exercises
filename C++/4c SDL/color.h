#ifndef _COLOR_H
#define _COLOR_H

// Eine Klasse, deren Objekte Farben (rot/grün/blau-Werte) darstellen
class Color
{
  // Den Konstruktor und die 3 Get-Methoden darf man überall aufrufen
  public:   
    // Konstuktor: Wird mit Farbwerten aufgerufen
    // und speichert die Farbwerte in den Member-Variablen des neuen Objektes.
    // Das sollte man mit einer Initialisierungsliste machen
    // (==> nächste Übung!).
    //
    // Dieser Konstruktur ist trickreich:
    // Er kann mit Farbwerten aufgerufen werden,
    // aber dient auf Grund der Default-Werte zugleich
    // als Standard-Konstruktor *ohne* Parameter.
    // Dann werden alle Farben per Default auf 0 gesetzt (schwarz).
    //
    // Color braucht unbedingt einen Standard-Konstruktor:
    // Sobald ein neues Point-Objekt angelegt wird, wird sein Color-Member mRGB
    // automatisch mittels Standard-Konstruktor initialisiert,
    // noch *bevor* der Point-Konstruktor dann die richtige Farbe hineinkopiert.
    Color(int r = 0, int g = 0, int b = 0): mR(r), mG(g), mB(b)
    {
    }
      
    // Destruktor brauchen wir keinen, der "automatische" genügt uns.

    // get-Methoden: Liefere den rot / grün / blau-Anteil der eigenen Farbe
    // (weil ja kein direkter Zugriff von außen auf die Member möglich ist).
    // Brauchen keine Parameter,
    // weil sie die Farben des eigenen Objektes liefern sollen,
    // und das eigene Objekt "this" wird jeder Methode automatisch mitgegeben.
    // Das komische "const" zwischen ) und { heißt,
    // dass das eigene Objekt (das "this") beim Aufruf unverändert bleibt,
    // d.h. dass die Methode die Werte in den eigenen Membern nicht ändert.
    int getR() const { return mR; }   // ist dasselbe wie { return this->mR; }
    int getG() const { return mG; }
    int getB() const { return mB; }

    // set-Methoden haben wir keine,
    // also kann man ein Farb-Objekt nicht mehr nachträglich ändern
    // (man muss stattdessen ein neues machen).

  // Kein Zugriff von klassenfremdem Code auf mR, mG, mB
  private:   
    // Member-Variablen:
    // Der Farbwert für rot, grün und blau in jedem Farb-Objekt
    // Dass sie m... heißen, ist nicht Pflicht, aber es ist sinnvoll,
    // damit sich Member auf einen Blick von anderen Variablen unterscheiden.
    int mR, mG, mB;
};  // wie bei Strukturen: ';' nicht vergessen!
#endif