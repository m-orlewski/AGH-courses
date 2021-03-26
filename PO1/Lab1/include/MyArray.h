#pragma once

#include <iostream>
#include <utility>

class MyArray
{
    friend std::ostream & operator<<(std::ostream & out, const MyArray & p);
private:
    int * _arr = nullptr;
    unsigned _size;
public:
//Konstruktory i destruktory
    MyArray(unsigned n=0);
    MyArray(const MyArray & p);
    MyArray(MyArray && p);
    ~MyArray();
//Metody publiczne
    void print(const char * str) const;
    int size() const { return static_cast<int>(_size); }
//Operatory
    int & operator[](unsigned i) const;
    void operator++();
    MyArray & operator=(const MyArray & p);
};

std::ostream & operator<<(std::ostream & out, const MyArray & p);