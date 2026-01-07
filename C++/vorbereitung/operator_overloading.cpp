#include <iostream>
using namespace std;

struct Number
{
    int value;

    Number(int v)
    {
        value = v;
    }

    // Overload + operator
    Number operator+(const Number &n)
    {
        return Number(value + n.value);
    }

    void display()
    {
        cout << value << endl;
    }
};

int main()
{
    Number n1(5), n2(10);
    Number n3 = n1 + n2;
    n3.display();
}