#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Exemplo: Classe Sorte com número gerado automaticamente

class Sorte{
    private:
        static int letzterWert;
        int nummer;

    public:
        Sorte(){
            nummer = ++letzterWert;
        }

        int getNummer() const {
            return nummer;
        }
};

int Sorte::letzterWert = 0;

int main(){
    Sorte s1;
    Sorte s2;
    Sorte s3;

    cout << s1.getNummer() << endl;
    cout << s2.getNummer() << endl;
    cout << s3.getNummer() << endl;

    return 0;
}
