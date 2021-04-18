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
    int iter = list.yield(multiply);
    while (iter != 0)
    {
        cout << iter << endl;
        iter = list.yield(multiply);
    }
    return 0;
}