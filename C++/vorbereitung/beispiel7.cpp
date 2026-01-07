//Array de objetos, strings...

#include <iostream>
#include <string>
using namespace std;

class Pessoa {
private:
    string nome;
    int idade;

public:
    Pessoa(string n = "Unbekannt", int i = 0) : nome(n), idade(i) {}

    void vorstellen() const {
        cout << "Ich heiße " << nome << " und bin " << idade << " Jahre alt." << endl;
    }
};

int main() {
    // 🔹 Array de objetos Pessoa
    Pessoa gruppe[3] = {
        Pessoa("Anna", 30),
        Pessoa("Ben", 25),
        Pessoa("Clara", 28)
    };

    cout << "Vorstellung der Gruppe:" << endl;
    for (int i = 0; i < 3; ++i) {
        gruppe[i].vorstellen();  // acesso com ponto
    }

    // 🔹 Array de strings
    string namen[3] = {"David", "Eva", "Frank"};

    cout << "\nNamen im String-Array:" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << namen[i] << endl;
    }

    return 0;
}