
#include <iostream>

class Konto {
    int kontostand{};
    inline static double zinssatz = 0.02; // klassenweiter Zinssatz (C++17+)

public:
    Konto& einzahlen(int betrag) { // nicht-static: hat this
        kontostand += betrag;
        return *this; // Fluent API
    }

    int getKontostand() const { return kontostand; }

    static void setZinssatz(double z) { // static: kein this
        if (z >= 0.0) zinssatz = z;
    }

    static double getZinssatz() { return zinssatz; }

    double voraussichtlicheZinsen() const {
        // Zugriff auf klassenweites Member in nicht-static Methode:
        return kontostand * zinssatz;
    }
};

int main() {
    Konto::setZinssatz(0.03);            // Aufruf der static Methode über Klasse
    Konto a; a.einzahlen(1000);          // this vorhanden
    std::cout << a.voraussichtlicheZinsen() << "\n";
}