# hyper-list is a library which lets you create flexible length arrays in C++

This means, You can create an array with a flexible length. It also comes with some prebuilt features like,

1. sort
2. binarySearch
3. linearSearch
4. insert
5. insertAt
6. append
7. filter
8. map
9. reduce
10. toArray

# Example usage

```C++
#include <iostream>
#include "hyper-list.hpp"
using namespace std;

int main()
{
    List<int> list;
    list[69] = 420; // As simple as that. No need to worry about the size of the list.
    cout << string(list) << endl;
    return 0;
}
```
