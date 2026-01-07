// Einfache Array-Klasse mit Operatoren
//
// Klaus Kusche, 2011

#include <iostream>

using namespace std;

class Array
{
  friend ostream &operator<<(ostream &outFile, const Array &a);

  public:
    Array(unsigned int sz) : size(sz), data(new double[sz]) {}
    Array(const Array &a);

    ~Array() {
      delete[] data;
    }

    unsigned int getSize() { return size; }
    double getVal(unsigned int index);
    bool setVal(unsigned int index, double val);

    Array operator+(const Array &a) const;
    Array operator+(double a) const;
    Array operator-() const;
    bool operator==(const Array &a) const;

    Array &operator=(const Array &a);
    Array &operator=(double val);
    Array &operator+=(const Array &a);
    
  private:
  
    unsigned int size;
    double *data;
};

Array::Array(const Array &a) : size(a.size), data(new double[size])
{
  for (unsigned int i = 0; i < size; ++i) {
    data[i] = a.data[i];
  }
}

double Array::getVal(unsigned int index)
{
  if (index < size) {
    return data[index];
  } else  {
    return 0;
  }
}

bool Array::setVal(unsigned int index, double val)
{
  if (index < size) {
    data[index] = val;
    return true;
  } else {
    return false;
  }
}

Array Array::operator+(const Array &a) const
{
  unsigned int n = (size < a.size) ? size : a.size;
  Array res(n);
  
  for (unsigned int i = 0; i < n; ++i) {
    res.data[i] = data[i] + a.data[i];
  }

  return res;
}

Array Array::operator+(double val) const
{
  Array res(size);
  
  for (unsigned int i = 0; i < size; ++i) {
    res.data[i] = data[i] + val;
  }

  return res;
}

Array Array::operator-() const
{
  Array res(size);
  
  for (unsigned int i = 0; i < size; ++i) {
    res.data[i] = -data[i];
  }

  return res;
}

bool Array::operator==(const Array &a) const
{
  if (size != a.size) return false;
  for (unsigned int i = 0; i < size; ++i) {
    if (data[i] != a.data[i]) return false;
  }

  return true;
}

Array &Array::operator=(const Array &a)
{
  if (this != &a) {
    if (size != a.size) {
      delete[] data;
      size = a.size;
      data = new double[size];
    }
    for (unsigned int i = 0; i < size; ++i) {
      data[i] = a.data[i];
    }
  }

  return *this;
}

Array &Array::operator=(double val)
{
  for (unsigned int i = 0; i < size; ++i) {
    data[i] = val;
  }
  
  return *this;
}

Array &Array::operator+=(const Array &a)
{
  // rechte Seite ist kürzer ==> eigenes Array kürzer machen
  if (size > a.size) {
    double *tmp = data;            // alte Daten merken!
    size = a.size;
    data = new double[size];
    for (unsigned int i = 0; i < size; ++i) { // ... und in neues Array kopieren
      data[i] = tmp[i];
    }
    delete[] tmp;
  }

  for (unsigned int i = 0; i < size; ++i) {
    data[i] += a.data[i];
  }

  return *this;
}

ostream &operator<<(ostream &outFile, const Array &a)
{
  for (unsigned int i = 0; i < a.size; ++i) {
    outFile << a.data[i] << ' ';
  }
  
  return outFile;
}

int main()
{
  Array a(5), b(2), c(10);

  a = 1.0;
  c = b = a;
  cout << "a == b: " << ((a == b) ? "gleich" : "ungleich") << endl;
  a.setVal(0, 10.0);
  b.setVal(1, 11.0);
  c.setVal(2, 12.0);
  a = a;
  cout << "a: " << a << ", b: " << b << ", c: " << c << endl;

  a = a + a;
  c = b + -a;
  b = b + 3.0;
  cout << "a: " << a << ", b: " << b << ", c: " << c << endl;
  cout << "a == b: " << ((a == b) ? "gleich" : "ungleich") << endl;

  Array kurz(2), lang(5), tmp(0);

  kurz = 9.9;
  lang = 9.9;
  cout << "kurz == lang: " << ((kurz == lang) ? "gleich" : "ungleich") << endl;
  kurz.setVal(0, 6.6);
  cout << "kurz + lang: " << kurz + lang << endl;
  cout << "lang + kurz: " << lang + kurz << endl;

  // auskommentieren, wenn += nicht implementiert ist!
  tmp = lang;
  tmp.setVal(1, 0.0);
  cout << "kurz: " << kurz << ", lang: " << lang << endl;
  lang += kurz;
  kurz += tmp;
  cout << "lang += kurz: " << lang << endl;
  cout << "kurz += tmp: " << kurz << endl;

  return 0;
}