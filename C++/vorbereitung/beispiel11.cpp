
#include <iostream>
#include <cstdlib>   // Para rand() e srand()
#include <ctime>     // Para time()

int main() {
    // Inicializa a semente do gerador de números aleatórios com o tempo atual
    srand(static_cast<unsigned int>(time(nullptr)));

    // Gera 10 números aleatórios entre 0 e 99
    for (int i = 0; i < 10; ++i) {
        int numero = rand() % 100; // rand() retorna um valor entre 0 e RAND_MAX
        std::cout << numero << " ";
    }

    std::cout << std::endl;
    return 0;
}
