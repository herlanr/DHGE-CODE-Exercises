
#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int alter;

public:
    // Konstruktor
    Person(const std::string& n, int a) : name(n), alter(a) {}

    // Getter (Get-Methoden)
    std::string getName() const {
        return name;
    }

    int getAlter() const {
        return alter;
    }

    // Setter (Set-Methoden)
    void setName(const std::string& n) {
        name = n;
    }

    void setAlter(int a) {
        if (a >= 0) { // einfache Validierung
            alter = a;
        }
    }
};

int main() {
    Person p("Herlan", 25);

    // Zugriff über Getter
    std::cout << "Name: " << p.getName() << ", Alter: " << p.getAlter() << "\n";

    // Änderung über Setter
    p.setName("Rocha");
    p.setAlter(26);

    std::cout << "Name: " << p.getName() << ", Alter: " << p.getAlter() << "\n";

    return 0;
}