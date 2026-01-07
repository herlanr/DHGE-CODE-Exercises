#include <iostream>

using namespace std;

class Node;
class MessList;

class Node{

    friend class MessList;
    friend ostream &operator<<(ostream &outfile, const Node &node);

    private:
        double value;
        Node *next;
    public:
        Node(double v): value(v), next(nullptr){}
};

class MessList{

    friend ostream &operator<<(ostream &outfile, const MessList &list);

    private:
        int anz;
        Node *head;
    public:
        MessList(): anz(0), head(nullptr){}
        MessList(const MessList &list);
        ~MessList(){
            while (head){
                Node *temp = head;
                head = head->next;
                delete temp;
            }
            anz = 0;
        }

        void append(double value){
            Node *n = new Node(value);
            if (!head){
                head = n;
            } else {
                Node *current = head;
                while(current->next){
                    current = current->next;
                }
                current->next = n;
            }

            ++anz;
        }

        int operator~() const { return anz; }
        bool operator!() const { return anz == 0; }
        double operator[](int i) const;
        MessList operator+(double x) const;
        MessList operator+(const MessList &list) const;
        MessList operator-(double x) const;
        MessList &operator-=(double x);
        MessList &operator+=(double x);
        MessList &operator+=(const MessList &list);
        MessList &operator=(const MessList &list);
        operator double() const;
};

MessList::MessList(const MessList &list): anz(0), head(nullptr){
    Node *current = list.head;
    while(current){
        append(current->value);
        current = current->next;
    }
}

double MessList::operator[](int i) const{
    if (i < 0 || i >= anz){
        throw "Index out of range";
    }

    Node *current = head;
    for (int j = 0; j < i; ++j){
        current = current->next;
    }

    return current->value;
}

MessList MessList::operator+(double x) const{
    MessList result(*this);
    result.append(x);
    return result;
}

MessList MessList::operator+(const MessList &list) const{
    MessList result(*this);
    Node *current = list.head;
    while (current){
        result.append(current->value);
        current = current->next;
    }
    return result;
}

MessList MessList::operator-(double x) const {
    MessList result(*this);   
    result -= x;              
    return result;
}

// Modifizierend: entfernt das erste Vorkommen von x in *this
MessList &MessList::operator-=(double x) {
    if (!head) return *this;

    // 1) Kopf trifft
    if (head->value == x) {
        Node* temp = head;
        head = head->next;
        delete temp;
        --anz;
        return *this;
    }

    // 2) Irgendwo in der Mitte/Ende
    Node* prev = head;
    Node* cur  = head->next;
    while (cur) {
        if (cur->value == x) {
            prev->next = cur->next;
            delete cur;
            --anz;
            break;   // nur erstes Vorkommen entfernen
               }
        prev = cur;
        cur  = cur->next;
    }
    return *this;
}

MessList &MessList::operator+=(double x){
    append(x);
    return *this;
}

MessList &MessList::operator+=(const MessList &list){
    Node *current = list.head;
    while(current){
        append(current->value);
        current = current->next;
    }
    return *this;
}

MessList &MessList::operator=(const MessList &list){
    // 1) Selbstzuweisung abfangen
    if (&list == this){
        return *this;
    }
    // 2) Eigene alten Knoten freigeben
    while(head){
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    // 3) Länge zurücksetzen
    anz = 0;

    // 4) Tief kopieren (Werte übernehmen)
    Node *current = list.head;
    while(current){
        append(current->value);
        current = current->next;
    }
    // 5) Rückgabe für Kettenzuweisunge
    return *this;
}

MessList::operator double() const{
    if(anz == 0){
        return 0;
    }

    double sum = 0;
    Node *current = head;
    while(current){
        sum += current->value;
        current = current->next;
    }

    return sum / anz;
}

ostream &operator<<(ostream &outfile, const Node &node){
    outfile << node.value;
    return outfile;
}

ostream &operator<<(ostream &outfile, const MessList &list){
    for(int i = 0; i < list.anz; ++i){
        outfile << list[i];
    }

    return outfile;
}

int main(){

    MessList a;
    a.append(1.0);
    a.append(2.0);
    a.append(3.0);

    a -= 1;

    cout << "a: " << a << "\n";
    cout << "~a (Anzahl): " << ~a << "\n";
    cout << "!a (leer?): " << (!a ? "ja" : "nein") << "\n";
    cout << "a[1]: " << a[1] << "\n";

    MessList b;
    b += 10.5;
    b += 20.5;
    cout << "b: " << b << "\n";

    MessList c = a + b;
    cout << "c = a + b: " << c << "\n";

    a += 4.0;
    cout << "a += 4.0: " << a << "\n";

    MessList d = c; // Copy-Konstruktor (Deep Copy)
    cout << "d (Kopie von c): " << d << "\n";

    cout << "Durchschnitt von d: " << double(d) << "\n";

    return 0;
}

