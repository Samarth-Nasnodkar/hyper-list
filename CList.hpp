#include <iostream>
using namespace std;

template <class elementType>
class List
{
private:
    elementType *list;
    long length;

public:
    List(long length = 1)
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
    List(const List &list)
    {
        list.length = this->length;
        list.list = new elementType[length];
        for (long i = 0; i < length && list.list[i] != NULL; i++)
            list.list[i] = this->list[i];
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
        extend(1);
        list[length - 1] = element;
        return *this;
    }
    elementType &operator[](long index)
    {
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
    long len()
    {
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

        return (flag) ? listLen : 0;
    }
    List &sort(bool reverse = false)
    {
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
        // list[len() - 1] = (elementType)NULL;
        elementType temp[length];
        long i;
        for (i = 0; i < length; i++)
            temp[i] = list[i];
        list = new elementType[length + extensionBy];
        for (i = 0; i < length; i++)
            list[i] = temp[i];
        // list[len] = (elementType)NULL;
        length += extensionBy;
        return *this;
    }
    long search(elementType element)
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
};