#include <iostream>

using namespace std;

class Node{
    friend class Tree;
    public:
        Node(string w): word(w), count(1), left(nullptr), right(nullptr) {}
    private:
        string word;
        int count;
        Node *left;
        Node *right;
};

class Tree{

    friend ostream &operator<<(ostream &outfile, const Tree &tree);

    private:
        Node *root;
        
        static void deleteRec(Node *root){
            if(root != nullptr){
                deleteRec(root->left);
                deleteRec(root->right);
                delete root;
            }
        }
        
    public:
        Tree(): root(nullptr){}
        ~Tree(){
            deleteRec(root);
        }

        void insert(Node *&node, string word){
            if(node == nullptr){
                node = new Node(word);
            } else if (word < node->word){
                insert(node->left, word);
            } else if (word > node->word){
                insert(node->right, word);
            } else {
                node->count++;
            }
        }

        

};

int main(){

}