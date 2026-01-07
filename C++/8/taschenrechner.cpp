#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Bruch{
    private:
        int z;
        int n;

    void Kuerze(); 

    public:
    //constructor
        Bruch(int zaehler = 0, int nenner = 1) : z(zaehler), n(nenner){
            Kuerze();
        }
    
};

int main(int argc, const char *argv[]){

}