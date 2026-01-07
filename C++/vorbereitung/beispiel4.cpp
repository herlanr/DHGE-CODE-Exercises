#include <iostream>

//Vererbung und overriding

using namespace std;

class Tier {
public:
    virtual void sprich() const {
        cout << "Ein Tier macht ein Geräusch." << endl;
    }
};

class Hund : public Tier {
public:
    void sprich() const override {
        cout << "Der Hund bellt." << endl;
    }
};