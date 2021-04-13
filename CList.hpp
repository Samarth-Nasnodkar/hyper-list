#include <iostream>
using namespace std;

template <class elementType> // elementType will be the class of the data which the array will store.
class List
{
private:
    elementType *list;
    long length; // The length of the array. This length is flexible and can be changed.

public:
    List(long length = 1) // Default constructer.
    {
        this->length = length;
        list = new elementType[length];
        list[0] = (elementType)NULL;
        if (length > 1)
        {
            for (long i = 1; i < length; i++)
                list[i] = (elementType)NULL;
        }
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
    operator string() const
    {
        string repr = "[";
        for (long i = 0; i < length; i++)
        {
            if (i == length - 1)
                repr += to_string(list[i]) + "]";
            else
                repr += to_string(list[i]) + ", ";
        }
        return repr;
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
            for (int i = len() - 1; i <= index; i++)
                list[i] = (elementType)NULL;
            return list[index];
        }
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
        for (long i = 0; i < length; i++)
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
    List &extend(long extensionBy)
    {
        /*
        This function extends the size of the list by the specified amount.
        All the new elements added will be NULL.
        */
        elementType *temp = new elementType[length];
        long i;
        for (i = 0; i < length; i++)
            temp[i] = list[i];
        list = new elementType[length + extensionBy];
        for (i = 0; i < length; i++)
            list[i] = temp[i];
        length += extensionBy;
        delete temp;
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
        If the array is sorted. It will conduct Binary Search else will do Linear Search.
        The array should be sorted in ascending order.
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
