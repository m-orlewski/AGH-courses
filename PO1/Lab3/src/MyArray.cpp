#include "../include/MyArray.h"

MyArray::MyArray(unsigned n): len(n)
{
    if (len)
    {
        arr = new int[len]{0};
    }
}

MyArray::MyArray(const MyArray & o): len(o.len), next(o.next)
{
    if (len)
    {
        arr = new int[len];
        for (unsigned i=0; i < len; i++)
        {
            arr[i] = o.arr[i];
        }
    }
}

MyArray::MyArray(MyArray && o): len(std::exchange(o.len, 0))
{
    arr = o.arr;
    o.arr = nullptr;

    next = o.next;
    o.next = nullptr;
}

MyArray::~MyArray()
{
    if (arr)
        delete [] arr;
}

int & MyArray::operator[](unsigned i) const
{
    if (i < len)
        return arr[i];
    else
    {
        if (next)
        {
            return (*next)[i-len];
        }
        else
        {
            std::cout << "Array index out of range.\n";
            exit(EXIT_FAILURE);
        }
    }
}

MyArray & MyArray::operator++()
{
    for (unsigned i=0; i < len; i++)
        arr[i]++;

    return *this;
}

MyArray MyArray::operator--(int)
{
    MyArray temp = *this;

    for (unsigned i=0; i < len; i++)
        arr[i]--;
    
    return temp;
}

MyArray & MyArray::operator=(const MyArray & o)
{
    if (this == &o)
        return *this;
    
    if (arr)
        delete [] arr;
    
    len = o.len;
    arr = new int[len];
    next = o.next;

    for (unsigned i=0; i < len; i++)
    {
        arr[i] = o.arr[i];
    }

    return *this;
}

void MyArray::operator+=(MyArray & o)
{
    if (!next)
    {
        next = &o;
        return;
    }

    MyArray * ptr = next;
    while (ptr->next)
    {
        ptr = ptr->next;
    }
    ptr->next = &o;
}

void MyArray::print(const char * str) const
{
    std::cout << str;
    MyArray const * ptr = this;
    while (ptr)
    {
        std::cout << *ptr << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
}

MyArray & MyArray::getNext() const
{
    return *next;
}

int MyArray::sizeall() const
{
    int all=0;
    MyArray const * ptr = this;
    while (ptr)
    {
        all += ptr->len;
        ptr = ptr->next;
    }
    return all;
}

void MyArray::operator+=(MyArray && o)
{  
    int new_len = len + o.len;
    int * new_arr = new int[new_len];

    unsigned i;
    for (i=0; i < len; i++)
    {
        new_arr[i] = arr[i];
    }
    for (unsigned j=0; j < o.len; j++)
    {
        new_arr[i+j] = o.arr[j];
    }

    delete [] arr;
    arr = new_arr;
    len = new_len;
}

std::ostream & operator<<(std::ostream & out, const MyArray & o)
{
    out << "[";
    for (unsigned i=0; i < o.len; i++)
    {
        out << o.arr[i];
        if (i+1 < o.len)
            std::cout << ", ";
    }
    out << "]";

    return out;
}