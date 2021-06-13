#include <iostream>
#include "hyper-list.hpp"
using namespace std;

int main()
{
    List<int> list(10);
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        list[i] = rand() % 100;
    }
    cout << "List : " << list << endl;
    // for (const auto item : list)
    //     cout << item << endl;

    return 0;
}