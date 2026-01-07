
#include <iostream>

class Buffer {
private:
    int* data;
    size_t size;

public:
    Buffer(size_t n) : size(n), data(new int[n]) {
        std::cout << "Buffer angelegt mit " << size << " Elementen.\n";
    }

    ~Buffer() { // Destruktor
        std::cout << "Buffer wird gelöscht. Speicher freigeben...\n";
        delete[] data; // Ressourcen freigeben
    }
};

int main() {
    Buffer b(10); // Konstruktor wird aufgerufen
    // Am Ende von main wird der Destruktor automatisch ausgeführt
}
