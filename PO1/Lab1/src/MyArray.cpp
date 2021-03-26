#include "../include/MyArray.h"

MyArray::MyArray(unsigned n): _size(n)
{
    std::cout << "Konstruktor...\n";
    if (_size)
    {
        _arr = new int[_size]{0};
        std::cout << "Alokuje " << _size << " elementow.\n";
    }
}

MyArray::MyArray(const MyArray & p)
{
    _size = p._size;
    _arr = new int[_size];

    for (unsigned i=0; i < _size; i++)
    {
        _arr[i] = p._arr[i];
    }
}

MyArray::MyArray(MyArray && p): _arr(std::exchange(p._arr, nullptr)), _size(std::exchange(p._size, 0))
{
}

MyArray::~MyArray()
{
    std::cout << "Destruktor...\n";
    if (_arr)
    {
        std::cout << "Usuwam tablice " << _size << " elementow.\n";
        delete [] _arr;
    }
}

void MyArray::print(const char * str) const
{
    std::cout << str << " = [";
    for (unsigned i=0; i < _size; i++)
    {
        std::cout << _arr[i] << ", ";
    }
    std::cout << "]\n";
}

int & MyArray::operator[](unsigned i) const
{
    if (i < _size)
    {
        return _arr[i];
    }
    else
    {
        std::cout << "Indeks poza tablica. Zwracam ostatni elemenent.\n";
        return _arr[_size-1];
    }
}

void MyArray::operator++()
{
    for (unsigned i=0; i < _size; i++)
    {
        _arr[i]++;
    }
}

MyArray & MyArray::operator=(const MyArray & p)
{
    if (this == &p)
    {
        return *this;
    }

    if (_arr)
    {
        delete [] _arr;
    }
    _size = p._size;
    _arr = new int[_size];
    for (unsigned i=0; i < _size; i++)
    {
        _arr[i] = p._arr[i];
    }
    return *this;
}

std::ostream & operator<<(std::ostream & out, const MyArray & p)
{
    out << "[";
    for (unsigned i=0; i < p._size; i++)
    {
        out << p._arr[i] << ", ";
    }
    return out << "]\n";
}