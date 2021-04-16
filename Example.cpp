#include <iostream>
#include "hyper-list.hpp"
using namespace std;

int sum(int a)
{
    return 5 * a;
}

int main()
{
    List<int> list;
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    auto newList = list.map(sum).toArray();
    int listLen = sizeof(newList) / sizeof(newList[0]);
    for (int i = 0; i <= listLen; i++)
        cout << newList[i] << endl;
    return 0;
}