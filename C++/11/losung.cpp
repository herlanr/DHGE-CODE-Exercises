// Zähler-Array-Klasse
//
// Aufruf: lotto
//
// Klaus Kusche, 2012

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

inline unsigned int max(unsigned int a, unsigned int b)
{
  return (a < b) ? b : a;
}

class Counter
{
  friend ostream &operator<<(ostream &outFile, const Counter &a);
  
  public:
    Counter(unsigned int sz);
    Counter(const Counter &a);

    ~Counter() {
      delete[] counts;
    }

    unsigned int getSize() const {
      return size;
    }

    // [] nur zum Lesen, nicht zum Ändern von Werten
    // ==> Return by Value statt wie sonst üblich by Reference
    int operator[](unsigned int val) const {
      return (val < size) ? counts[val] : 0;
    }

    Counter operator+(const Counter &a) const;
    Counter operator+(unsigned int val) const;
    int operator~() const;
    bool operator<=(const Counter &a) const;

    Counter &operator=(const Counter &a);
    
  private:
    unsigned int size;
    int *counts;
};

Counter::Counter(unsigned int sz) : size(sz), counts(new int[sz])
{
  for (unsigned int i = 0; i < size; ++i) {
    counts[i] = 0;
  }
}

Counter::Counter(const Counter &a) : size(a.size), counts(new int[size])
{
  for (unsigned int i = 0; i < size; ++i) {
    counts[i] = a.counts[i];
  }
}

/* Variante für gleiche Größe
Counter Counter::operator+(const Counter &a) const
{
  if (a.size != size) {
    cerr << "operator+: different size" << endl;
    exit(EXIT_FAILURE);
  }
  
  Counter res(size);
  for (unsigned int i = 0; i < size; ++i) {
    res.counts[i] = counts[i] + a.counts[i];
  }

  return res;
}
*/

Counter Counter::operator+(const Counter &a) const
{
  unsigned int s = max(size, a.size);
  Counter res(s);
  for (unsigned int i = 0; i < s; ++i) {
    // Statt direktem Zugriff auf das Member counts[i]:
    // Unsere Get-Methode [] verwenden!
    // Vorteil: Für nicht existierende Elemente liefert unser [] gleich 0
    // Sonst bräuchten wir eine Schleife für die gemeinsamen Elemente vorne
    // und eine zweite Schleife für die Elemente des längeren Operanden hinten
    // (*this)[i] ... Operator [] aufgerufen für das eigene Objekt
    res.counts[i] = (*this)[i] + a[i];
  }

  return res;
}

/* Variante für gleiche Größe
Counter Counter::operator+(unsigned int val) const
{
  if (val >= size) {
    cerr << "operator+: val out of bounds" << endl;
    exit(EXIT_FAILURE);
  }

  // Ergebnis-Objekt gleich als Kopie des eigenen Objektes anlegen!
  Counter res(*this);   
  ++res.counts[val];

  return res;
}
*/

Counter Counter::operator+(unsigned int val) const
{
  // Bei einem val außerhalb unserer Länge
  // machen wir das Ergebnis entsprechend länger
  unsigned int s = max(size, val + 1);
  Counter res(s);
  for (unsigned int i = 0; i < s; ++i) {
    res.counts[i] = (*this)[i];  // siehe Kommentar bei operator +
  }
  ++res.counts[val];

  return res;
}

int Counter::operator~() const
{
  int sum = 0;                
  for (unsigned int i = 0; i < size; ++i) {
    sum += counts[i];         
  }
  return sum;                 
}


/* Variante für gleiche Größe
bool Counter::operator<=(const Counter &a) const
{
  if (a.size != size) {
    cerr << "operator<=: different size" << endl;
    exit(EXIT_FAILURE);
  }

  for (unsigned int i = 0; i < size; ++i) {
    if (counts[i] > a.counts[i]) return false;
  }

  return true;
}
*/

bool Counter::operator<=(const Counter &a) const
{
  unsigned int s = max(size, a.size);
  for (unsigned int i = 0; i < s; ++i) {
    if ((*this)[i] > a[i]) return false;  // siehe Kommentar bei operator +
  }

  return true;
}

/* Variante für gleiche Größe
Counter &Counter::operator=(const Counter &a)
{
  if (this != &a) {
    if (a.size != size) {
      cerr << "operator=: different size" << endl;
      exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < size; ++i) {
      counts[i] = a.counts[i];
    }
  }

  return *this;
}
*/

Counter &Counter::operator=(const Counter &a)
{
  if (this != &a) {        // Bei a = a nichts tun!
    if (a.size != size) {  // Größe des Arrays im eigenen Objekt ändern
      delete[] counts;
      size = a.size;
      counts = new int[size];
    }
    for (unsigned int i = 0; i < size; ++i) {
      counts[i] = a.counts[i];
    }
  }

  return *this;
}

ostream &operator<<(ostream &outFile, const Counter &a)
{
  for (unsigned int i = 0; i < a.size; ++i) {
    if (a.counts[i] > 0) {   // Nur die Zähler größer 0 werden ausgegeben
      outFile << i << ':' << a.counts[i] << ' ';
    }
  }
  
  return outFile;
}

const int kugeln = 49;
const int zahlen = 6;

Counter ziehe();

Counter ziehe()
{
  Counter res(kugeln);

  while (~res < zahlen) {   // bis genug Zahlen gezogen sind
    // "würfle" eine Zahl z
    unsigned int z = rand() % kugeln;
    if (res[z] == 0) {
      // wenn noch nicht gezogen: Erhöhe genau diesen Zähler um 1
      res = res + z;
    }
  }

  return res;
}

int main(void)
{
  srand(time(nullptr));

  Counter ziehung(kugeln), gezogen(kugeln);
  int i;

  for (i = 1; ; ++i) {
    ziehung = ziehe();
    // kommen alle Zahlen in "ziehung" auch in "gezogen" vor?
    if (ziehung <= gezogen) break;
    // gib die gerade gezogenen Zahlen zur Summe aller bisher gezogenen dazu
    gezogen = gezogen + ziehung;
  }

  cout << i << " Runden" << endl;
  cout << ziehung << endl;
  cout << gezogen << endl;

  exit(EXIT_SUCCESS);
}