#include <iostream>
#include <string>
using namespace std;

// Classe base genérica para elementos da árvore
template <typename T>
class BaumElement {
protected:
    T wert;
public:
    BaumElement(T w) : wert(w) {}
    virtual void anzeigen() const = 0;
    T getWert() const { return wert; }
};

// Nó da árvore com filhos
template <typename T>
class Knoten : public BaumElement<T> {
private:
    Knoten<T>* links;
    Knoten<T>* rechts;
public:
    Knoten(T w) : BaumElement<T>(w), links(nullptr), rechts(nullptr) {}

    void setLinks(Knoten<T>* l) { links = l; }
    void setRechts(Knoten<T>* r) { rechts = r; }
    
    Knoten* getRechts() const {
        return rechts;
    }

    Knoten* getLinks() const {
        return links;
    }

    void anzeigen() const override {
        cout << "Wert: " << this->wert << endl;
    }

    // Função recursiva: soma de todos os valores
    T summe() const {
        T sum = this->wert;
        if (links) sum += links->summe();
        if (rechts) sum += rechts->summe();
        return sum;
    }

    // Função não recursiva: busca por valor
    bool suche(T ziel) const {
        const Knoten<T>* current = this;
        while (current) {
            if (current->wert == ziel) return true;
            current = (ziel < current->wert) ? current->links : current->rechts;
        }
        return false;
    }
};

// Folha da árvore
template <typename T>
class Blatt : public BaumElement<T> {
public:
    Blatt(T w) : BaumElement<T>(w) {}
    void anzeigen() const override {
        cout << "Blatt: " << this->wert << endl;
    }
};

// Função auxiliar: contar elementos (recursiva)
template <typename T>
int zaehleKnoten(const Knoten<T>* knoten) {
    if (!knoten) return 0;
    return 1 + zaehleKnoten(knoten->getLinks()) + zaehleKnoten(knoten->getRechts());
}

// Função auxiliar: maior valor (recursiva)
template <typename T>
T maxWert(const Knoten<T>* knoten) {
    if (!knoten->getRechts()) return knoten->getWert();
    return maxWert(knoten->getRechts());
}

// MAIN
int main() {
    Knoten<int>* wurzel = new Knoten<int>(10);
    Knoten<int>* links = new Knoten<int>(5);
    Knoten<int>* rechts = new Knoten<int>(15);
    wurzel->setLinks(links);
    wurzel->setRechts(rechts);

    wurzel->anzeigen();
    cout << "Summe: " << wurzel->summe() << endl;
    cout << "Suche 15: " << (wurzel->suche(15) ? "Gefunden" : "Nicht gefunden") << endl;
    cout << "MaxWert: " << maxWert(wurzel) << endl;

    delete wurzel;
    delete links;
    delete rechts;
    return 0;
}