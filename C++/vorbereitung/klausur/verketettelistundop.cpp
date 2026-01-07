#include <iostream>
using namespace std;

class MessListe {
    struct Node {
        double wert;
        Node* next;
        Node(double w, Node* n = nullptr) : wert(w), next(n) {}
    };

    Node* head;
    int anz;

public:
    MessListe() : head(nullptr), anz(0) {}
    MessListe(const MessListe& orig);
    ~MessListe();

    // Anzahl der Werte
    int operator~() const { return anz; }

    // Ist die Liste leer?
    bool operator!() const { return anz == 0; }

    // [] Zugriff auf i-tes Element (nur lesen)
    double operator(int i) const;

    // + fügt einen Wert hinzu (neue Liste)
    MessListe operator+(double x) const;

    // + hängt zwei Listen zusammen (neue Liste)
    MessListe operator+(const MessListe& r) const;

    // += fügt Wert hinzu (in-place)
    MessListe& operator+=(double x);

    // += hängt Liste an (in-place)
    MessListe& operator+=(const MessListe& r);

    // Mittelwert als Typumwandlung
    operator double() const;

    // Zuweisungsoperator
    MessListe& operator=(const MessListe& r);

    friend ostream& operator<<(ostream& out, const MessListe& l);
};

// Copy-Konstruktor
MessListe::MessListe(const MessListe& orig) : head(nullptr), anz(0) {
    Node* p = orig.head;
    while (p) {
        *this += p->wert;
        p = p->next;
    }
}

// Destruktor
MessListe::~MessListe() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

// [] Zugriff
double MessListe::operator(int i) const {
    if (i < 0 || i >= anz) return 0;
    Node* p = head;
    for (int k = 0; k < i; ++k) p = p->next;
    return p->wert;
}

// + Wert hinzufügen
MessListe MessListe::operator+(double x) const {
    MessListe neu(*this);
    neu += x;
    return neu;
}

// + Liste anhängen
MessListe MessListe::operator+(const MessListe& r) const {
    MessListe neu(*this);
    neu += r;
    return neu;
}

// += Wert hinzufügen
MessListe& MessListe::operator+=(double x) {
    Node* neu = new Node(x);
    if (!head) {
        head = neu;
    } else {
        Node* p = head;
        while (p->next) p = p->next;
        p->next = neu;
    }
    ++anz;
    return *this;
}

// += Liste anhängen
MessListe& MessListe::operator+=(const MessListe& r) {
    Node* p = r.head;
    while (p) {
        *this += p->wert;
        p = p->next;
    }
    return *this;
}

// Mittelwert
MessListe::operator double() const {
    if (anz == 0) return 0;
    double sum = 0;
    Node* p = head;
    while (p) {
        sum += p->wert;
        p = p->next;
    }
    return sum / anz;
}

// Zuweisung
MessListe& MessListe::operator=(const MessListe& r) {
    if (this != &r) {
        this->~MessListe(); // alte Liste löschen
        head = nullptr;
        anz = 0;
        Node* p = r.head;
        while (p) {
            *this += p->wert;
            p = p->next;
        }
    }
    return *this;
}

// Ausgabeoperator
ostream& operator<<(ostream& out, const MessListe& l) {
    Node* p = l.head;
    while (p) {
        out << p->wert << " ";
        p = p->next;
    }
    return out;
}

// Test im main
int main() {
    MessListe l1;
    l1 += 1.2;
    l1 += 3.4;
    l1 += 5.6;

    MessListe l2;
    l2 += 7.8;
    l2 += 9.0;

    cout << "Liste 1: " << l1 << endl;
    cout << "Liste 2: " << l2 << endl;

    MessListe l3 = l1 + l2;
    cout << "Liste 3 (zusammen): " << l3 << endl;

    cout << "Mittelwert L3: " << double(l3) << " (" << ~l3 << " Werte)" << endl;
    cout << "Erstes Element: " << l3[0] << ", letztes: " << l3[~l3 - 1] << endl;

    return 0;
}