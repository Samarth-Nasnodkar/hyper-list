#include <iostream>
#include "hyper-list.hpp"
using namespace std;

double times2(double a)
{
    return a * 2;
}

int main()
{
    List<double> list(6);
    list[0] = 1;
    list[1] = 9;
    list[2] = 15;
    list.insert(69);
    cout << string(list) << endl;
    list.setYieldFunction(times2);
    double iter = list.yield();
    while (iter)
    {
        cout << iter << endl;
        iter = list.yield();
    }
    cout << list.len() << endl;
    return 0;
}