#include <iostream>
#include "hyper-list.hpp"
using namespace std;

char UPPERCASE(char a)
{
    return toupper(a);
}

int main()
{
    List<char> list;
    list[0] = 'a';
    list[1] = 'b';
    list[2] = 'c';
    char iter = list.yield(UPPERCASE);
    while (iter != (char)NULL)
    {
        cout << iter << endl;
        iter = list.yield(UPPERCASE);
    }
    return 0;
}