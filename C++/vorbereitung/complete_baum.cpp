#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class Node{

    template <typename U>
    friend class Tree;

    //Ausgabe-Operator für den einzelnen Knoten
    template <typename U>
    friend ostream &operator<<(ostream &outfile, const Node<U> *node);

    //Ausgabe-Operator für den (Teil-) Baum 
    template <typename U>
    friend ostream &operator<<(ostream &outfile, const Node<U> &nodeObj);

    private:
        T data;
        Node<T> *left;
        Node<T> *right;
    public:
        Node(T d): data(d), left(nullptr), right(nullptr){}
};

template <typename T>
class Tree{

    //Ausgabe-Operator für den gesamten Baum
    template <typename U>
    friend ostream &operator<<(ostream &outfile, const Tree<U> &tree);

    private:
        Node<T> *root;

        // 1º Rekursiv Funktion
        void deleteRec(Node<T> *root){
            if(root){
                deleteRec(root->left);
                deleteRec(root->right);
                delete root;
            }
        }

        // 2º Rekursiv Funktion
        void insertRec(Node<T>* &node, const T &data) {
            if (node == nullptr) {
                node = new Node<T>(data);
            } else if (data < node->data) {
                insertRec(node->left, data);
            } else {
                insertRec(node->right, data);
            }
        }

        //1º Funktion Denksport - easy
        int height(Node<T>* node) const {
            if (!node) return 0;
            return 1 + max(height(node->left), height(node->right));
        }

        //2º Funktion Denksport - easy
        int countLeaves(Node<T>* node) {
            if (!node) return 0; // Base case: empty subtree has 0 leaves
            if (!node->right && !node->left) return 1; // If node has no children, it's a leaf
            return countLeaves(node->left) + countLeaves(node->right); // Otherwise, sum leaves from both subtrees
        }

        //3º Funktion Denksport - easy
        int countNodes(Node<T>* node) const {
            if (!node) return 0;
            return 1 + countNodes(node->left) + countNodes(node->right);
        }

        //4º Funktion Denksport - easy
        T sumValues(Node<T>* node) const {
            if (!node) return 0;
            return node->data + sumValues(node->left) + sumValues(node->right);
        }

        //5º Funktion Denksport - hard
        bool isBalanced(Node<T>* node) const {
            if (!node) return true;
            int lh = height(node->left);
            int rh = height(node->right);
            return abs(lh - rh) <= 1 && isBalanced(node->left) && isBalanced(node->right);
        }

    public:
        Tree(): root(nullptr){}
        Tree(const Tree<T> &tree) = delete;
        ~Tree(){
            deleteRec(root);
        }

        void insert(const T &data) {
            insertRec(root, data);
        }

        Node<T>* deleteNode(Node<T>* node, const T& value) {
            if (!node) return nullptr; // Base case: empty tree

            if (value < node->data) {
                node->left = deleteNode(node->left, value);
            } else if (value > node->data) {
                node->right = deleteNode(node->right, value);
            } else {
                // Found the node to delete
                // Case 1: Leaf node
                if (!node->left && !node->right) {
                    delete node;
                    return nullptr;
                }
                // Case 2: Node has one child
                else if (!node->left || !node->right) {
                    Node<T>* child = (node->left) ? node->left : node->right;
                    delete node;
                    return child;
                }
                // Case 3: Node has two children
                else {
                    // Find successor (smallest value in right subtree)
                    Node<T>* successor = node->right;
                    while (successor->left) {
                        successor = successor->left;
                    }
                    // Copy successor's value to current node
                    node->data = successor->data;
                    // Delete successor recursively
                    node->right = deleteNode(node->right, successor->data);
                }
            }
            return node;
        }

        //1º gezielt auf ein einzelnes Baumelement
        bool contains(const T &value){
            Node<T> *current = root;
            while(current){
                if (current->data == value){
                    return true;
                }
                if(value < current->data){
                    current = current->left;
                } else {
                    current = current->right;
                }
            }

            return false;
        }

        //2º gezielt auf eine einzelnes Bauelement
        void remove(const T& value) {
            root = deleteNode(root, value);
        }

        int getHeight(){
            return height(root);
        }

        int getLeavesCount(){
            return countLeaves(root);
        }

        int getNodesCount(){
            return countNodes(root);
        }

        T getSumValues(){
            return sumValues(root);
        }

        bool isBalanced(){
            return isBalanced(root);
        }

};

//ausgabe einzelnen Knoten
template <typename T>
ostream &operator<<(ostream &outfile, const Node<T> &nodeObj){
    outfile << "Value: " << nodeObj.data;
    return outfile;
};

//ausgabe teilbaum
template <typename T>
ostream &operator<<(ostream &outfile, const Node<T> *node){
    if (node != nullptr){
        outfile << node->left;
        outfile << *node << endl;
        outfile << node->right;
    }

    return outfile;
};

//ausgabe baum
template <typename T>
ostream &operator<<(ostream &outfile, const Tree<T> &tree){
    outfile << tree.root;
    return outfile;
};

// 1) Rekursiv über alle Elemente (Inorder-Anwenden)
template <typename T, typename Func>
void inorderApply(const Node<T>* node, Func f) {
    if (!node) return;
    inorderApply(node->left, f);
    f(node->data);
    inorderApply(node->right, f);
}

// 2) Iterativ: gezielt ein einzelnes Baumelement (Minimum / linkester Knoten)
template <typename T>
const Node<T>* findMinNode(const Tree<T>& tree) {
    const Node<T>* cur = tree.getRoot();
    if (!cur) return nullptr;
    while (cur->left) cur = cur->left;
    return cur;
}

int main() {

    Tree<int> intTree;
    intTree.insert(10);
    intTree.insert(5);
    intTree.insert(15);
    intTree.insert(3);
    intTree.insert(7);
    intTree.insert(12);
    intTree.insert(18);
    intTree.remove(15);

    cout << "Integer Tree:\n" << intTree << endl;

    cout << "Contains 7? " << (intTree.contains(7) ? "Yes" : "No") << endl;
    cout << "Height: " << intTree.getHeight() << endl;
    cout << "Number of leaves: " << intTree.getLeavesCount() << endl;
    cout << "Number of nodes: " << intTree.getNodesCount() << endl;
    cout << "Sum of values: " << intTree.getSumValues() << endl;
    cout << "Is balanced? " << (intTree.isBalanced() ? "Yes" : "No" ) << endl;

    // Instance with double
    Tree<double> doubleTree;
    doubleTree.insert(10.5);
    doubleTree.insert(5.2);
    doubleTree.insert(15.8);

    cout << "\nDouble Tree:\n" << doubleTree << endl;

    // Instance with string
    Tree<string> stringTree;
    stringTree.insert("Maria");
    stringTree.insert("Joao");
    stringTree.insert("Ana");

    cout << "\nString Tree:\n" << stringTree << endl;

    return 0;
}