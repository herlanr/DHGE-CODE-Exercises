//dynamisches angelegtes array

#include <iostream>
#include <string>
using namespace std;

int main() {
    int tamanho;
    cout << "Quantas pessoas deseja armazenar? ";
    cin >> tamanho;

    // Criando array dinâmico
    string* pessoas = new string[tamanho];

    // Preenchendo o array
    for (int i = 0; i < tamanho; ++i) {
        cout << "Digite o nome da pessoa " << (i + 1) << ": ";
        cin >> pessoas[i];
    }

    // Imprimindo os nomes
    cout << "\nLista de pessoas:" << endl;
    for (int i = 0; i < tamanho; ++i) {
        cout << pessoas[i] << endl;
    }

    // Liberando memória
    delete[] pessoas;

    return 0;
}