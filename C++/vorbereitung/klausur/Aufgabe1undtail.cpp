
#include <iostream>
#include <stdexcept>

using namespace std;

class Node;
class MessList;

class Node {
    friend class MessList;
    friend ostream& operator<<(ostream& out, const Node& node);
private:
    double value;
    Node* next;
public:
    explicit Node(double v) : value(v), next(nullptr) {}
};

class MessList {
    friend ostream& operator<<(ostream& out, const MessList& list);

private:
    int   anz;
    Node* head;
    Node* tail; // NOVO: ponteiro para o último nó

public:
    MessList() : anz(0), head(nullptr), tail(nullptr) {}

    // Copy constructor (deep copy) usando append O(1)
    MessList(const MessList& other) : anz(0), head(nullptr), tail(nullptr) {
        Node* cur = other.head;
        while (cur) {
            append(cur->value);
            cur = cur->next;
        }
    }

    ~MessList() {
        clear();
    }

    MessList& operator=(const MessList& other) {
        if (this == &other) return *this;
        clear();
        Node* cur = other.head;
        while (cur) {
            append(cur->value);
            cur = cur->next;
        }
        return *this;
    }

    // ======== Operações básicas =========
    void append(double value) {
        Node* n = new Node(value);
        if (!head) {
            head = tail = n; // lista antes vazia
        } else {
            tail->next = n;  // anexar no fim
            tail = n;        // atualizar tail
        }
        ++anz;
    }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        anz = 0;
    }

    // ======== Operadores utilitários =========
    int  operator~() const { return anz; }            // quantidade
    bool operator!() const { return anz == 0; }       // vazio?

    double operator[](int i) const {
        if (i < 0 || i >= anz) throw out_of_range("Index out of range");
        Node* cur = head;
        for (int j = 0; j < i; ++j) cur = cur->next;
        return cur->value;
    }

    // Converte para média (0 se vazia)
    operator double() const {
        if (anz == 0) return 0.0;
        double sum = 0.0;
        for (Node* cur = head; cur; cur = cur->next) sum += cur->value;
        return sum / anz;
    }

    // ======== + e += com double e com lista =========
    MessList operator+(double x) const {
        MessList res(*this);
        res.append(x);
        return res;
    }

    MessList operator+(const MessList& rhs) const {
        MessList res(*this);
        for (Node* cur = rhs.head; cur; cur = cur->next) res.append(cur->value);
        return res;
    }

    MessList& operator+=(double x) {
        append(x);
        return *this;
    }

    MessList& operator+=(const MessList& rhs) {
        for (Node* cur = rhs.head; cur; cur = cur->next) append(cur->value);
        return *this;
    }

    // ======== Remoção do primeiro x (modifica a lista) =========
    MessList operator-(double x) const {
        MessList res(*this);
        res -= x;
        return res;
    }

    MessList& operator-=(double x) {
        if (!head) return *this;

        // Caso 1: remover cabeça
        if (head->value == x) {
            Node* doomed = head;
            head = head->next;
            // Se removemos o único nó, tail deve virar nullptr
            if (doomed == tail) tail = nullptr;
            delete doomed;
            --anz;
            return *this;
        }

        // Caso 2: remover no meio/fim (precisamos do anterior)
        Node* prev = head;
        Node* cur  = head->next;
        while (cur) {
            if (cur->value == x) {
                prev->next = cur->next;
                // Se removemos o último nó, atualizar tail
                if (cur == tail) tail = prev;
                delete cur;
                --anz;
                break; // remove só o primeiro
            }
            prev = cur;
            cur  = cur->next;
        }
        return *this;
    }

    // (opcionais) métodos de acesso para prova
    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }
};

ostream& operator<<(ostream& out, const Node& node) {
    return out << node.value;
}

ostream& operator<<(ostream& out, const MessList& list) {
    for(int i = 0; i < list.anz; ++i){
        out << list[i];
    }

    return out;
}

// ======== Demonstração ========
int main() {
    MessList a;
    a.append(1.0);
    a.append(2.0);
    a.append(3.0);

    a -= 1.0; // remove primeiro 1.0
    cout << "a: " << a << "\n";               // [2, 3]
    cout << "~a (Anzahl): " << ~a << "\n";    // 2
    cout << "!a (leer?): " << (!a ? "ja" : "nein") << "\n";
    cout << "a[1]: " << a[1] << "\n";         // 3

    MessList b;
    b += 10.5;
    b += 20.5;
    cout << "b: " << b << "\n";               // [10.5, 20.5]

    MessList c = a + b;
    cout << "c = a + b: " << c << "\n";       // [2, 3, 10.5, 20.5]

    a += 4.0;
    cout << "a += 4.0: " << a << "\n";        // [2, 3, 4]

    MessList d = c; // copy ctor
    cout << "d (Kopie von c): " << d << "\n";
    cout << "Durchschnitt von d: " << double(d) << "\n";

    return 0;
}