//wie bekomme ich einen Pointer auf so ein lokales Objekt

#include <iostream>
using namespace std;

class Person {
public:
    void sagHallo() const {
        cout << "Hallo!" << endl;
    }
};

int main() {
    Person p;              // objeto local
    Person* ptr = &p;      // ponteiro para o objeto local

    ptr->sagHallo();       // acesso via ponteiro
    return 0;
}