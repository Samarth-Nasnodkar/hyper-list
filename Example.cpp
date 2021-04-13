#include <iostream>
#include "CList.hpp"
using namespace std;

int main()
{
    List<float> list;
    list[31] = 420;
    cout << string(list) << endl;
    return 0;
}