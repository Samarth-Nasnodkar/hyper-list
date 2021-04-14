#include <iostream>
#include "hyper-list.hpp"
using namespace std;

int main()
{
    List<int> l1;
    l1[6] = 9;
    List<int> l2;
    l2[5] = 0;
    l2.append(9);
    bool equality = (l1 == l2);
    if (equality)
        cout << "Equal.\n";
    else
        cout << "Not equal.\n";
    return 0;
}