// Operatoren, dyn. Arrays: Klassen für Messwerte
//
// Aufruf: messw filename1 filename2 ...
//
// Klaus Kusche, 2018

#include <iostream>
#include <fstream>

using namespace std;

class Messw
{
  friend ostream &operator<<(ostream &outFile, const Messw &r);

  public:
    Messw() : anz(0), arr(nullptr) { } // Standard-Konstruktor: "Leeres" Objekt
    Messw(const Messw &orig);
  
    ~Messw() {
      delete [] arr;
    }

    // ~ liefert die Anzahl der Messwerte im Objekt = Arraygröße
    int operator~() const {
      return anz;
    }

    // "Not": Ist das Objekt leer?
    bool operator!() const {
      return anz == 0;
    }

    // [] nur zum Lesen des i-ten Elementes
    // (zum Lesen und Ändern müsste eine Referenz zurückgegeben werden!)
    double operator[](int i) const {
      if ((i < 0) || (i >= anz)) {
        return 0;
      }
      return arr[i];
    }

    // füge einen einzelnen Wert zu einer Messreihe dazu
    Messw operator+(double x) const;
    // hänge zwei Messreihen zusammen
    Messw operator+(const Messw &r) const;

    // optional: +=
    // erweitere eine Messreihe um einen Wert
    Messw &operator+=(double x);
    // erweitere eine Messreihe um eine Messreihe
    Messw &operator+=(const Messw &r);

    // Typumwandlungs-Operator von Messreihe auf double
    // (Returntyp implizit double)
    // liefert den Mittelwert der Messreihe
    operator double() const;

    Messw &operator=(const Messw &r);
    
  private:
    // wir machen das Array immer genau so groß,
    // wie wir es für die momentan zu speichernden Messwerte brauchen
    // "angelegte Arraygröße" und "Anzahl belegter Elemente" ist dasselbe!
    int anz;
    double *arr;  // Pointer auf das dynamisch angelegte Array

    // nur klassenintern verwendbarer Konstruktor:
    // liefert ein Messw-Objekt mit einem Array der angegebenen Größe
    // die Elemente des Arrays bleiben uninitialisiert!
    Messw(int a) : anz(a), arr(new double[a]) { }
};

Messw::Messw(const Messw &orig) : anz(orig.anz), arr(new double[anz])
{
  for (int i = 0; i < anz; ++i) {
    arr[i] = orig.arr[i];
  }
}

Messw Messw::operator+(double x) const
{
  Messw ergeb(anz + 1);
  for (int i = 0; i < anz; ++i)
  {
    ergeb.arr[i] = arr[i];
  }
  ergeb.arr[anz] = x;
  return ergeb;
}

Messw Messw::operator+(const Messw &r) const
{
  Messw ergeb(anz + r.anz);
  for (int i = 0; i < anz; ++i)
  {
    ergeb.arr[i] = arr[i];
  }
  for (int i = 0; i < r.anz; ++i)
  {
    ergeb.arr[anz + i] = r.arr[i];
  }
  return ergeb;
}

Messw &Messw::operator+=(double x)
{
  // Kein neues Objekt, sondern nur ein neues Array anlegen
  // (in einer Hilfsvariable, denn wir brauchen das alte Array noch!)
  double *arr_neu = new double[anz + 1]; 
  for (int i = 0; i < anz; ++i)
  {
    arr_neu[i] = arr[i];
  }
  arr_neu[anz] = x;
  // Altes Array im eigenen Objekt freigeben und durch neues Array ersetzen
  delete [] arr;
  arr = arr_neu;
  // ... und eigene Größe aktualisieren
  ++anz;
  // Wie bei operator=: Geändertes eigenes Objekt (= linker Operand) zurückgeben
  return *this;
}

Messw &Messw::operator+=(const Messw &r)
{
  // Gleiche Vorgehensweise wie bei vorigem +=
  double *arr_neu = new double[anz + r.anz]; 
  for (int i = 0; i < anz; ++i)
  {
    arr_neu[i] = arr[i];
  }
  for (int i = 0; i < r.anz; ++i)
  {
    arr_neu[anz + i] = r.arr[i];
  }
  delete [] arr;
  arr = arr_neu;
  anz += r.anz;
  return *this;
}

Messw::operator double() const
{
  if (anz == 0) {
    return 0;
  }
  double sum = 0;
  for (int i = 0; i < anz; ++i) {
    sum += arr[i];
  }
  return sum / anz;
}

Messw &Messw::operator=(const Messw &r)
{
  if (this != &r) {       // Schutz gegen Selbstzuweisung
    if (r.anz != anz) {   // eigenes Array hat falsche Größe
      delete [] arr;      // ==> wegwerfen und neu anlegen
      anz = r.anz;
      arr = new double[anz];
    }
    for (int i = 0; i < r.anz; ++i)
    {
      arr[i] = r.arr[i];
    }
  }
  return *this;
}

ostream &operator<<(ostream &outFile, const Messw &r)
{
  for (int i = 0; i < r.anz; ++i) {
    outFile << r.arr[i] << " ";
  }
  return outFile; 
}

int main(int argc, const char *argv[])
{
  Messw alle;

  for (int i = 1; i < argc; ++i) {
    ifstream inFile(argv[i]);
    if (!inFile) {
      cerr << argv[0] << ": Fehler beim Öffnen von "
           << argv[i] << endl;
      continue;  // überspring den File, mach mit dem nächsten File weiter
    }
    Messw diese;
    double a;
    
    while (inFile >> a) {
      // Wahlweise: Einfaches + für einen Wert ...
      //diese = diese + a;
      // ... oder += für einen Wert
      diese += a;
    }
    
    cout << "Datei " << argv[i] << ": ";
    if (!diese) {
      cout << "Keine Werte!" << endl;
    } else {
      cout << diese << endl;
    }
    cout << "Mittelwert: " << double(diese)
           << " (" << ~diese << " Werte)\n" << endl;

    // Wahlweise: Einfache + für eine ganze Messreihe 
    //alle = alle + diese;
    // ... oder += für eine ganze Messreihe
    alle += diese;
  }
  
  cout << alle[0] << " ... " << alle[~alle - 1] << endl;
  cout << "Mittelwert insgesamt: " << double(alle)
       << " (" << ~alle << " Werte)" << endl;
  
  return 0;
}