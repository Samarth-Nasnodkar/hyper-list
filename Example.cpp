#include <iostream>
#include "CList.hpp"
using namespace std;

int main()
{
    List<int> list;
    list[5] = 6;
    list.extend(6);
    cout << string(list) << endl;
    return 0;
}