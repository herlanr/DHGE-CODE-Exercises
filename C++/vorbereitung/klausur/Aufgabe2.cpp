
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T> 
class Node {
    template <typename U> friend class Tree;
    template <typename U> friend ostream& operator<<(ostream& o, const Node<U>& nodeObj);
    template <typename U> friend ostream& operator<<(ostream& o, const Node<U>* nodePtr);

private:
    T        data;
    Node<T>* left;
    Node<T>* right;

public:
    Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

template <typename T>
class ITree {
public:
    virtual ~ITree() = default;
    virtual void insert(const T& data) = 0;
    virtual bool contains(const T& data) = 0;
    virtual void remove(const T& data) = 0;
};

template <typename T>
class Statistiken {
public:
    virtual ~Statistiken() = default;
    virtual T   getSumOfValues() const = 0;
    virtual int getHeight() const = 0;
/*     T findMax() const {} //optional
    T findMin() const {} //optional
    int getLeavesCount() const{} //optional
    int getNodesCount() const{} //optional */
};

template <typename T>
class Tree : public ITree<T>, public Statistiken<T> {
    template <typename U>
    friend ostream& operator<<(ostream& o, const Tree<U>& tree);

private:
    Node<T>* root;

    static void insertRec(Node<T>*& node, const T& data) {
        if (!node) {
            node = new Node<T>(data);
        } else if (data < node->data) {
            insertRec(node->left, data);
        } else {
            insertRec(node->right, data);
        }
    }

    static void deleteRec(Node<T>* node) {
        if (!node) return;
        deleteRec(node->left);
        deleteRec(node->right);
        delete node;
    }

    static int height(Node<T>* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    static T sumOfValues(Node<T>* node) {
        if (!node) return T{}; // neutraler Wert
        return node->data + sumOfValues(node->left) + sumOfValues(node->right);
    }

    // Entfernen: einfache Fälle (Blatt, genau ein Kind)
    static void removeValue(Node<T>*& node, const T& value) {
        if (!node) return;

        if (value < node->data) {
            removeValue(node->left, value);
        } else if (value > node->data) {
            removeValue(node->right, value);
        } else {
            // === node->data == value: Treffer ===

            // Fall A: Blatt
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            }
            // Fall B: genau ein Kind
            else if (!node->left || !node->right) {
                Node<T>* child = (node->left ? node->left : node->right);
                delete node;
                node = child;
            }
            // Fall C: zwei Kinder (nicht gefordert)
            else {
                // Konzept: Inorder-Nachfolger/vorgänger finden, Wert kopieren, Nachfolger löschen
                // -> hier bewusst ausgelassen (Klausur: Konzept kennen, Code nicht verlangt)
                // (Optional) Kommentar statt Exception:
                // // Zwei-Kinder-Fall hier nicht implementiert.
            }
        }
    }

    bool pcontains(const T &data)
    {
        if (!root)
            return false;
        Node<T> *current = root;
        while (current)
        {
            if (current->data == data)
            {
                return true;
            }
            current = (data < current->data) ? current->left : current->right;
        }
        return false;
    }

public:
    Tree() : root(nullptr) {}
    Tree(const Tree<T>&) = delete;
    Tree& operator=(const Tree<T>&) = delete;
    ~Tree() { deleteRec(root); }

    void insert(const T& data) override {
        insertRec(root, data);
    }

    bool contains(const T& data) override {
        return pcontains(data);
    }

    void remove(const T& data) override {
        removeValue(root, data);  
    }

    T getSumOfValues() const override {
        return sumOfValues(root);
    }

    int getHeight() const override {
        return height(root);
    }
};

// Ausgabe: einzelner Knoten (Objekt)
template <typename T>
ostream& operator<<(ostream& o, const Node<T>& nodeObj) {
    o << nodeObj.data;
    return o;
}

// Ausgabe: (Teil-)Baum via Node* (Inorder)
template <typename T>
ostream& operator<<(ostream& o, const Node<T>* nodePtr) {
    if (!nodePtr) return o;
    o << nodePtr->left;
    o << nodePtr->data << ' ';
    o << nodePtr->right;
    return o;
}

// Ausgabe: ganzer Baum
template <typename T>
ostream& operator<<(ostream& o, const Tree<T>& tree) {
    o << tree.root; // nutzt Node<T>*-Operator
    return o;
}

int main() {
    // kleine Smoke-Tests (Template-Instanzen)
    Tree<int> ti;
    ti.insert(10);
    ti.insert(5);
    ti.insert(15);
    ti.insert(7);
    ti.remove(5); // Blatt löschen

    cout << "INT-Baum inorder: " << ti << "\n";
    cout << "contains(7): " << (ti.contains(7) ? "true" : "false") << "\n";
    cout << "height: " << ti.getHeight() << "\n";
    cout << "sum: " << ti.getSumOfValues() << "\n";

    Tree<double> td;
    td.insert(10.5);
    td.insert(5.2);
    td.insert(15.8);
    td.remove(10.5); // Wurzel löschen -> ein Kind oder Blatt
    cout << "DOUBLE-Baum inorder: " << td << "\n";
    cout << "sum: " << td.getSumOfValues() << "\n";

    Tree<string> ts;
    ts.insert("Maria");
    ts.insert("Ana");
    ts.insert("Joao");
    cout << "STRING-Baum inorder: " << ts << "\n";
    cout << "sum (concat): " << ts.getSumOfValues() << "\n";

    return 0;
}