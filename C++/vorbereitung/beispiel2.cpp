#include <iostream>
using namespace std;

//Exemplo completo: Gerador de IDs com método estático

class IDGenerator {
private:
    static int nextID;

public:
    static int generateID() {
        return nextID++;
    }

    static int getLastID() {
        return nextID - 1;
    }
};

// Definição do membro estático fora da classe
int IDGenerator::nextID = 1;

int main() {
    // Chamada de métodos estáticos diretamente pela classe
    int id1 = IDGenerator::generateID();
    int id2 = IDGenerator::generateID();
    int id3 = IDGenerator::generateID();

    cout << "ID 1: " << id1 << endl;
    cout << "ID 2: " << id2 << endl;
    cout << "ID 3: " << id3 << endl;

    cout << "Letzte vergebene ID: " << IDGenerator::getLastID() << endl;

    return 0;
}