#include <iostream>
#include "hyper-list.hpp"
using namespace std;

int multiply(int a)
{
    return 5 * a;
}

int main()
{
    List<int> list;
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    const List<int> newList = list.map(multiply);
    for (const auto element : newList)
        cout << element << endl;
    return 0;
}