# CList is a library which lets you use Lists from Python in C++

This means, You can create an array with a flexible length. It also comes with some prebuilt features like,

1. sort
2. smartSearch
3. binarySearch
4. linearSearch
5. insert
6. insertAt
7. append

# Example usage

```C++
#include <iostream>
#include "CList.hpp"
using namespace std;

int main()
{
    List<int> list;
    list[69] = 420; // As simple as that. No need to worry about the size of the list.
    cout << string(list) << endl;
    return 0;
}
```
