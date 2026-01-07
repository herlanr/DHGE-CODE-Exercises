
#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int alter;

    // klassenweites (static) Member
    static int anzahlInstanzen;

public:
    Person(std::string n, int a) : name(std::move(n)), alter(a) {
        ++anzahlInstanzen;
    }

    ~Person() {
        --anzahlInstanzen;
    }

    // "Get für klassenweites Member": static Getter
    static int getAnzahlInstanzen() {
        return anzahlInstanzen; // erlaubt in static, weil das Member selbst static ist
    }

    // normale (nicht-static) Get/Set
    const std::string& getName() const { return name; }
    int getAlter() const { return alter; }
    void setAlter(int a) { if (a >= 0) alter = a; }
};

// Definition des static Members (Pflicht außerhalb der Klasse bis C++17)
int Person::anzahlInstanzen = 0;

int main() {
    std::cout << "Instanzen: " << Person::getAnzahlInstanzen() << "\n"; // Klassenaufruf

    Person a{"Herlan", 25};
    Person b{"Rocha", 26};

    // Aufruf über Klasse (empfohlen für static):
    std::cout << "Instanzen: " << Person::getAnzahlInstanzen() << "\n";

    // Aufruf über Objekt (möglich, aber weniger klar):
    std::cout << "Instanzen: " << a.getAnzahlInstanzen() << "\n";
}