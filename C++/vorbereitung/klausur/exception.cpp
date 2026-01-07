
#include <iostream>
#include <string>
#include <cctype>   // isspace
#include <cstdlib>  // strtod

using namespace std;

class SyntaxError
{
    friend ostream &operator<<(ostream &outF, const SyntaxError &err);

public:
    SyntaxError(const string &errMsg, const string &errInput, int errLine)
        : msg(errMsg), input(errInput), line(errLine) {}

private:
    const string msg, input;  // Fehlermeldungstext & falsche Input-Zeile
    int line;                 // Zeilennummer
};

ostream &operator<<(ostream &outFile, const SyntaxError &err)
{
    outFile << "Syntax error at line " << err.line << ": " << err.msg << endl;
    outFile << err.input << endl;
    return outFile;
}

int main() {
    int lineNr = 1;          // linha atual (simples, incrementa manualmente)
    std::string input;

    std::cout << "Geben Sie eine Zeile ein (nur Zahl erlaubt, Leerzeile beendet):\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, input)) {
            // EOF: terminar
            break;
        }
        if (input.empty()) {
            // Linha vazia: terminar
            std::cout << "Ende.\n";
            break;
        }

        try {
            // Tentar converter para número e validar que não há lixo depois
            const char* beg = input.c_str();
            char* end = nullptr;

            double value = std::strtod(beg, &end);

            // Nenhuma conversão possível
            if (beg == end) {
                throw SyntaxError("No number found", input, lineNr);
            }

            // Verificar se após o número há apenas espaços
            while (*end != '\0') {
                if (!std::isspace(static_cast<unsigned char>(*end))) {
                    throw SyntaxError("Text following after value", input, lineNr);
                }
                ++end;
            }

            // Se chegamos aqui, a linha é válida
            std::cout << "OK: Wert = " << value << "\n";
        }
        catch (const SyntaxError& e) {
            // Imprime a mensagem formatada via operator<<
                       std::cerr << e;
        }

        ++lineNr; // próxima linha
    }

    return 0;
}