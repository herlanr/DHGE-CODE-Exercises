//dynamische anlegen (mit new) und Statische / automatische Objekterzeugung (ohne new)

#include <iostream>

using namespace std;

class Person{
    private:
        string name;
        int alter;

    public:
        Person(string n, int a): name(n), alter(a){}

        void vorstellen() const{
            cout << "Ich heisse " << name << " und bin " << alter << " Jahre alt" << endl;
        }
};

int main(){
    // automatisch angelegtes Objekt (stack)
    Person p1("Anna", 30);
    p1.vorstellen();

    //dynamisch angelestes Objekt (heap)
    Person *p2 = new Person("Ben", 25);
    p2->vorstellen();

    delete p2;

    return 0;
}