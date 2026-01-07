#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

template <typename T>
class AbstractTree{
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
};

template <|

int main(){

};