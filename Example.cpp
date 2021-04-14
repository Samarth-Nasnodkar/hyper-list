#include <iostream>
#include "hyper-list.hpp"
using namespace std;

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    List<int> list;
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    int Sum = list.reduce(sum);
    cout << "The sum of all elements of the list is " << Sum << endl; // The sum of all elements of the list is 6
}