#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

// Classe abstrata
template <typename T>
class AbstractTree {
public:
    virtual ~AbstractTree() = default;

    virtual void insert(const T &data) = 0;
    virtual void remove(const T &data) = 0;
    virtual bool contains(const T &value) = 0;
    virtual int getHeight() = 0;
    virtual int getLeavesCount() = 0;
    virtual int getNodesCount() = 0;
    virtual T getSumValues() = 0;
    virtual bool isBalanced() = 0;

    // Operador de saída para qualquer árvore
    virtual void print(ostream &outfile) const = 0;
};

// Classe Node permanece igual
template <typename T>
class Node {
    template <typename U>
    friend class Tree;

    template <typename U>
    friend ostream &operator<<(ostream &outfile, const Node<U> *node);

private:
    T data;
    Node<T> *left;
    Node<T> *right;

public:
    Node(T d) : data(d), left(nullptr), right(nullptr) {}
};

// Classe Tree herda de AbstractTree
template <typename T>
class Tree : public AbstractTree<T> {
private:
    Node<T> *root;

    void deleteRec(Node<T> *root) {
        if (root) {
            deleteRec(root->left);
            deleteRec(root->right);
            delete root;
        }
    }

    void insertRec(Node<T> *&node, const T &data) {
        if (!node) {
            node = new Node<T>(data);
        } else if (data < node->data) {
            insertRec(node->left, data);
        } else {
            insertRec(node->right, data);
        }
    }

    int height(Node<T> *node) const {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    int countLeaves(Node<T> *node) {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }

    int countNodes(Node<T> *node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    T sumValues(Node<T> *node) const {
        if (!node) return 0;
        return node->data + sumValues(node->left) + sumValues(node->right);
    }

    bool isBalanced(Node<T> *node) const {
        if (!node) return true;
        int lh = height(node->left);
        int rh = height(node->right);
        return abs(lh - rh) <= 1 && isBalanced(node->left) && isBalanced(node->right);
    }

    Node<T> *deleteNode(Node<T> *node, const T &value) {
        if (!node) return nullptr;
        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            } else if (!node->left || !node->right) {
                Node<T> *child = node->left ? node->left : node->right;
                delete node;
                return child;
            } else {
                Node<T> *successor = node->right;
                while (successor->left) successor = successor->left;
                node->data = successor->data;
                node->right = deleteNode(node->right, successor->data);
            }
        }
        return node;
    }

public:
    Tree() : root(nullptr) {}
    ~Tree() { deleteRec(root); }

    // Implementação dos métodos abstratos
    void insert(const T &data) override { insertRec(root, data); }
    void remove(const T &data) override { root = deleteNode(root, data); }
    bool contains(const T &value) override {
        Node<T> *current = root;
        while (current) {
            if (current->data == value) return true;
            current = (value < current->data) ? current->left : current->right;
        }
        return false;
    }
    int getHeight() override { return height(root); }
    int getLeavesCount() override { return countLeaves(root); }
    int getNodesCount() override { return countNodes(root); }
    T getSumValues() override { return sumValues(root); }
    bool isBalanced() override { return isBalanced(root); }

    void print(ostream &outfile) const override {
        outfile << root;
    }
};

// Operadores de saída
template <typename T>
ostream &operator<<(ostream &outfile, const Node<T> *node) {
    if (node) {
        outfile << node->left;
        outfile << node->data << " ";
        outfile << node->right;
    }
    return outfile;
}

int main() {
    AbstractTree<int> *tree = new Tree<int>();
    tree->insert(10);
    tree->insert(5);
    tree->insert(15);
    tree->remove(15);

    cout << "Tree: ";
    tree->print(cout);
    cout << "\nHeight: " << tree->getHeight() << endl;
    cout << "Balanced? " << (tree->isBalanced() ? "Yes" : "No") << endl;

    delete tree;
    return 0;
}
