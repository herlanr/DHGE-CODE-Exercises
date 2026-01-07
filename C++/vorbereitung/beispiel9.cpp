#include <iostream>
#include <string>
using namespace std;

// Classe base
class Los {
public:
    Los(string kunde) : mKunde(kunde) {
        cout << "Los-Konstruktor für " << mKunde << endl;
    }

    virtual ~Los() {
        cout << "Los-Destruktor für " << mKunde << endl;
    }

    void info() const {
        cout << "Los für Kunde: " << mKunde << endl;
    }

    virtual int gewinnRang() const = 0;  // rein virtuelle Methode

protected:
    string mKunde;
};

// Classe derivada
class ZahlenLos : public Los {
public:
    ZahlenLos(string kunde, int zahl) : Los(kunde), mZahl(zahl) {
        cout << "ZahlenLos-Konstruktor mit Zahl: " << mZahl << endl;
    }

    ~ZahlenLos() {
        cout << "ZahlenLos-Destruktor für Zahl: " << mZahl << endl;
    }

    int gewinnRang() const override {
        return mZahl % 10;  // Exemplo simples de cálculo
    }

    void info() const {
        Los::info();  // Chamada do método da classe base
        cout << "ZahlenLos mit Zahl: " << mZahl << endl;
    }

private:
    int mZahl;
};

// Função principal
int main() {
    Los* los = new ZahlenLos("Herlan", 37);
    los->info();  // Chama info() da classe derivada, que chama a da base
    cout << "Gewinnrang: " << los->gewinnRang() << endl;

    delete los;  // Chama destrutores corretamente graças ao virtual
    return 0;
}