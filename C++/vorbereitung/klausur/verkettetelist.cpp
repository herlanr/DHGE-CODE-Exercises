#include <iostream>

using namespace std;

struct Node{
    int data;
    Node *next;
};

class LinkedList{

    friend ostream &operator<<(ostream &outfile, LinkedList &list); 

    private:
        Node *head;
    public:
        LinkedList(): head(nullptr){}
        ~LinkedList(){
            Node *current = head;
            while (current){
                Node *temp = current;
                current = current->next;
                delete temp;
            }
        }

        void append(int value);
        void print() const;
        bool search(int value) const;
        void removeFirst();
};

ostream &operator<<(ostream &outfile, LinkedList &list) {
    Node *current = list.head;
    while (current) {
        outfile << "Value: " << current->data << " ";
        current = current->next;
    }
    return outfile;
}

void LinkedList::append(int value){
    Node *newNode = new Node{value, nullptr};
    if (head == nullptr){
        head = newNode;
    } else {
        Node* current = head;
        while (current->next){
            current = current->next;
        }
        current->next = newNode;
    }
}

bool LinkedList::search(int value) const{
    Node *current = head;
    while(current){
        if(current->data == value){
            return true;
        }
        current = current->next;
    }

    return false;
}

void LinkedList::removeFirst(){
    if(head){
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

int main(){

}