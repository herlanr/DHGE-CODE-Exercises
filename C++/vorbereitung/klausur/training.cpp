#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class Node{

    template <typename U>
    friend class Tree;

    template <typename U>
    friend ostream &operator<<(ostream &out, const Node<U> *nodePtr);

    template <typename U>
    friend ostream &operator<<(ostream &out, const Node<U> &nodeObj);

    private:
        T data;
        Node<T> *right;
        Node<T> *left;
    public:
        Node(T d): data(d), right(nullptr), left(nullptr){}
};

template <typename T>
class Statistiken{
    public:
        virtual ~Statistiken() = default;
        virtual int getHeight() const = 0;
        virtual int getCountNodes() const = 0;
        virtual int getCountLeaves() const = 0;
        virtual T getSumOfValues() const = 0;
        virtual T findMax() const = 0;
        virtual T findMin() const = 0;
};

template <typename T>
class BaseTree{
    public:
        virtual ~BaseTree() = default;
        virtual void insert(const T &data) = 0;
        virtual void remove(const T &data) = 0;
        virtual bool contains(const T &data) const = 0;
};

template <typename T>
class Tree: public BaseTree<T>, public Statistiken<T>{

    template <typename U>
    friend ostream &operator<<(ostream &out, const Tree<U> &tree);

    public:
        Tree(): root(nullptr){}
        Tree(const Tree<T> &tree) = delete;
        Tree &operator=(const Tree<T> &tree) = delete;
        ~Tree(){
            deleteRec(root);
        }

        int getHeight() const override { return height(root); }
        int getCountNodes() const override { return countNodes(root); }
        int getCountLeaves() const override { return countLeaves(root); }
        T getSumOfValues() const override { return sumOfValues(root); }
        T findMax() const override { return findMax(root); }
        T findMin() const override { return findMin(root); }

        void insert(const T &data) override { insertRec(root, data); }
        void remove(const T &data) override { removeRec(root, data); }
        bool contains(const T &data) const override { return containsImpl(data); }

    private:
        Node<T> *root;

        static void deleteRec(Node<T>* &node){
            if(node){
                deleteRec(node->left);
                deleteRec(node->right);
                delete node;
            }
        }

        static int height(const Node<T> *node) { 
            if(!node) { return 0; }
            return 1 + max(height(node->left), height(node->right));
        }

        static int countNodes(const Node<T> *node) { 
            if(!node) { return 0; }
            return 1 + countNodes(node->left) + countNodes(node->right);
        }

        static int countLeaves(const Node<T> *node) { 
            if (!node) return 0;
            if (!node->left && !node->right) return 1;
            return countLeaves(node->left) + countLeaves(node->right);
        }

        static T sumOfValues(const Node<T> *node) {
             if(!node) {return T{};}
             return node->data + sumOfValues(node->left) + sumOfValues(node->right);
        }
        
        static T findMax(const Node<T> *node) { 
            if(!node){ throw "Tree is empty";}
            return (node && node->right) ? findMax(node->right) : node->data; 
        }

        static T findMin(const Node<T> *node) { 
            if(!node) {throw "Tree is empty"; }
            return (node && node->left) ? findMin(node->left) : node->data;
         }

        static void insertRec(Node<T>* &node, const T &data) { 
            if(!node){
                node = new Node<T>(data);
            } else if (data < node->data){
                insertRec(node->left, data);
            } else {
                insertRec(node->right, data);
            }
        }

        static void removeRec(Node<T>* &node, const T &data) { 
            if (!node) { return; }

            if (data < node->data){
                removeRec(node->left, data);
            } else if (data > node->data){
                removeRec(node->right, data);
            } else {

                if(!node->left && !node->right){
                    delete node;
                    node = nullptr;
                }

                else if(!node->left || !node->right){
                    Node<T> *child = (node->left) ? node->left : node->right;
                    delete node;
                    node = child;
                }

                else {
                    //nicht gefordet
                }
            }

        }

        bool containsImpl(const T &data) const { 
            if(!root) { return false; }

            const Node<T> *current = root;
            while(current){
                if(current->data == data){
                    return true;
                } else if(data < current->data){
                    current = current->left;
                } else {
                    current = current->right;
                }
            }

            return false;
        }

        
};