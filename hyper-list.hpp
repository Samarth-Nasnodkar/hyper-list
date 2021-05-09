#include <iostream>
#include <cstring>
#include <cstdlib>
#include <functional>

template <class elementType> // elementType will be the class of the data which the array will store.
class List
{
private:
    elementType *list;
    long length; // The length of the array. This length is flexible and can be changed.
    long yieldIndex = 0;
    std::function<elementType(elementType)> yieldF;

public:
    List(long length = 1) // Default constructer.
    {
        this->length = length;
        list = new elementType[length];
    }
    List(const List<elementType> &copyList)
    {
        length = copyList.length;
        list = new elementType[length];
        for (long i = 0; i < length; i++)
            list[i] = copyList.list[i];
    }
    List(List<elementType> &copyList)
    {
        length = copyList.length;
        list = new elementType[length];
        for (long i = 0; i < length; i++)
            list[i] = copyList.list[i];
    }
    operator std::string() const
    {
        std::string repr = "[";
        for (long i = 0; i < length; i++)
        {
            if (i == length - 1)
                repr += std::to_string(list[i]) + "]";
            else
                repr += std::to_string(list[i]) + ", ";
        }
        return repr;
    }
    List &setYieldFunction(elementType func(elementType), bool resetCounter = true)
    {
        yieldF = func;
        if (resetCounter)
            yieldReset();
        return *this;
    }
    List &yieldReset()
    {
        yieldIndex = 0;
        return *this;
    }
    elementType yield(elementType func(elementType) = NULL)
    {
        /*
        This function spits out one element at a time after passing it through the
        passed in function. This means you do not need another data structure to hold 
        all the elements and can easily iterate once at a time.
        Example usage,
        int squared(int value){
            return value*value;
        }
        If we declare a list, 
        List<int> list;
        with the elements [1, 2, 3, 4, 5]
        Then we can iterate through them by using
        int iter = list.yield(sum);
        while(iter != 0){
            cout<<iter<<endl;
            iter = list.yield(sum);
        }
        Everytime you use yield, it will spit out the next number.
        Here the output will be:
        1
        4
        9
        16
        25
        */
        if (func)
        {
            yieldF = func;
        }
        if (yieldIndex < length)
        {
            yieldIndex++;
            return yieldF(list[yieldIndex - 1]);
        }
        return (elementType)NULL;
    }
    List &append(elementType element)
    {
        /*
        This function adds the new element to the end of this array.
        Thus also increasing the length of the List by 1.
        */
        extend(1);
        list[length - 1] = element;
        return *this;
    }
    List<elementType> filter(bool func(elementType))
    {
        /*
        This function resembles the filter function from JavaScript.
        The parameter for the function is each element of the list.
        It returns a list of only the elements which return true when passed as parameters in the function.
        Example Usage,
        bool isPositiveNumber(int a){
            return a > 0;
        }
        This function can be used to filter out all positive elements from list by using,
        List<int> filteredList = list.filter(isPositiveNumber);
        */
        List<elementType> output;
        long increment = 0;
        for (long i = 0; i < length; i++)
        {
            if (func(list[i]))
            {
                output[increment] = list[i];
                increment++;
            }
        }
        return output;
    }
    List<elementType> map(elementType func(elementType))
    {
        /*
        This function resembles the map function from JavaScript.
        The parameter for the function is each element of the list.
        It then returns another list with the modified values through the function.
        Example Usage,
        int tripleValue(int a){
            return 3 * a;
        }
        This function can be used to triple the value of each element of an int list using,
        List<int> outputList = list.map(tripleValue);
        Here, each element of the outputList will be three times the corresponding element in list.
        */
        List<elementType> output;
        for (long i = 0; i < length; i++)
            output[i] = func(list[i]);

        return output;
    }
    elementType reduce(elementType func(elementType, elementType))
    {
        /*
        This function resembles the reduce function from JavaScript.
        The first parameter is called accumulator and the second parameter is the element of the list.
        It iterates through the list with the accumulator being passed on to the next element.

        Example usage,
        int sum(int a, int b){
            return a + b;
        }

        This function can be used to find the sum of all values of an integer list by using,
        int Sum = list.reduce(sum);
        It is that easy.
        */
        elementType accumulator = list[0];
        for (long i = 1; i < length; i++)
        {
            accumulator = func(accumulator, list[i]);
        }
        return accumulator;
    }
    elementType *toArray()
    {
        /*
        Returns the array form of the list.
        */
        return list;
    }
    elementType &operator[](long index)
    {
        /*
        This function returns the element at the specified position.
        It takes care of managing the length of the list as well.
        */
        if (index < length)
            return list[index];
        else
        {
            extend(index - length + 1);
            return list[index];
        }
    }
    bool operator==(List<elementType> &comparator)
    {
        if (length != comparator.length)
            return false;
        for (long i = 0; i < length; i++)
            if (list[i] != comparator[i])
                return false;

        return true;
    }
    List &insert(elementType element)
    {
        /*
        This function inserts the element at the first position(0th index).
        It pushes all other elements by 1 and also increases the size of the List by 1.
        */
        if (length == 0)
            list[0] = element;
        else
        {
            extend(1);
            list[length - 1] = list[length - 2];
            elementType temp;
            for (long i = length - 2; i > 0; i--)
            {
                list[i] = list[i - 1];
            }
            list[0] = element;
        }
        return *this;
    }
    List &insertAt(elementType element, long index)
    {
        /*
        This function lets you add the element at the specific position.
        It will push all elements after that element by 1.
        It also increases the size of the List by 1.
        */
        if (index > length)
            this->operator[](index) = element;
        else
        {
            extend(1);
            list[length - 1] = list[length - 2];
            elementType temp;
            for (long i = length - 2; i > index; i--)
            {
                list[i] = list[i - 1];
            }
            list[index] = element;
        }
        return *this;
    }
    bool isSorted()
    {
        bool definer = true;
        for (long i = 0; i < length && definer; i++)
        {
            if (list[i] > list[i + 1])
                definer = false;
        }
        return definer;
    }
    long len()
    {
        /*
        This funtion returns the practical length of the list.
        This means if the list has all NULL elements, it returns 0.
        Otherwise will return the length of the list
        */
        long listLen = 0;
        bool flag = false;
        while (listLen < length)
        {
            if (list[listLen] != (elementType)NULL)
            {
                flag = true;
            }
            listLen++;
        }

        return (flag) ? listLen : 0L;
    }
    List &sort(bool reverse = false)
    {
        /*
        This function will sort the list.
        It can be done in two ways. Ascending and Descending(reverse).
        */
        elementType temp;
        long currLen = len();
        bool swapped = false;
        for (long i = 0; i < currLen - 1; i++)
        {
            swapped = false;
            for (long j = 0; j < currLen - i - 1; j++)
            {
                if ((list[j] > list[j + 1] && !reverse) || (list[j] < list[j + 1] && reverse))
                {
                    temp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }
        return *this;
    }
    const elementType *begin() const
    {
        return &list[0];
    }
    const elementType *end() const
    {
        return &list[length];
    }
    List &extend(long extensionBy)
    {
        /*
        This function extends the size of the list by the specified amount.
        All the new elements added will be NULL.
        */
        elementType *temp = new elementType[length];
        memmove(temp, list, sizeof(list[0]) * length);
        list = new elementType[length + extensionBy];
        memmove(list, temp, sizeof(temp[0]) * length);
        length += extensionBy;
        return *this;
    }
    long BinarySearch(elementType element)
    {
        /*
        This function will conduct a Binary Search for the ascending array.
        It doesnt check if the array is sorted or not and might not give the correct
        value if the array is not sorted. So If you do not know if your array is sorted then
        conduct smartSearch
        */
        long high = length;
        long low = 0L;
        long mid;
        while (low < high)
        {
            mid = (low + high) / 2;
            if (list[mid] == element)
                return mid;
            else if (list[mid] > element)
                high = mid;
            else if (list[mid] < element)
                low = mid + 1L;
        }
        return -1L;
    }
    long linearSearch(elementType element)
    {
        /*
        This function will conduct a Linear Search and retrive the index of the element.
        However this can get a bit slow when dealing with large lists.
        */
        for (long i = 0; i < length; i++)
            if (list[i] == element)
                return i;

        return -1L;
    }
    long smartSearch(elementType element)
    {
        /*
        This function will Search an element.
        If the array is sorted it will conduct Binary Search else will do Linear Search.
        */
        bool sorted = isSorted();
        if (!sorted)
        {
            long high = length;
            long low = 0L;
            long mid;
            while (low < high)
            {
                mid = (low + high) / 2;
                if (list[mid] == element)
                    return mid;
                else if (list[mid] > element)
                    high = mid;
                else if (list[mid] < element)
                    low = mid + 1L;
            }
            return -1L;
        }
        else
        {
            for (long i = 0; i < length; i++)
                if (list[i] == element)
                    return i;

            return -1L;
        }
    }
};
