# CList is a library which lets you use Lists from Python in C++
This means, You can create an array with a flexible length. It also comes with some prebuilt features like,  
1. sort  
2. search(Binary search)
3. insert
4. insertAt
5. append

# Example usage
```C++
#include <iostream>
#include "CList.hpp"
using namespace std;

int main()
{
    List<int> list;
    list[69] = 420;
    cout << string(list) << endl;
    return 0;
}
```
