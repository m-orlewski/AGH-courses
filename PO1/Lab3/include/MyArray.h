#pragma once

#include <iostream>
#include <cstdlib>
#include <utility>

class MyArray
{
    friend std::ostream & operator<<(std::ostream & out, const MyArray & o);
private:
    int * arr=nullptr;
    unsigned len;
    MyArray * next=nullptr;
public:
    //! Konstruktor alokuje pamiec dla n intów
    MyArray(unsigned n=0);

    //! Konstruktor kopiujący (głęboka kopia)
    MyArray(const MyArray & o);

    //! Konstruktor przenoszący (dodaje o na koniec aktualnej listy obiektów)
    MyArray(MyArray && o);

    //! Destruktor (usuwa pamięc)
    ~MyArray();

    //! Zwraca rozmiar tablicy obiektu this
    int size() const {return len;}

    //! Zwraca wskaźnik na następny obiekt w liście
    MyArray & getNext() const;

    //! Wypisuje całą listę (z podziałem na obiekty)
    void print(const char * str) const;

    //! Zwraca sumę rozmiarów wszystkich tablic
    int sizeall() const;

    //! Zwraca i-ty element w liście
    int & operator[](unsigned i) const;

    //! Inkrementuje wszystkie elementy tablicy(pre)
    MyArray & operator++();

    //! Dekrementuje wszystkie elementy tablicy(post)
    MyArray operator--(int);

    //! Przypisuje zawartość obiektu o
    MyArray & operator=(const MyArray & o);

    //! Dodaje obiekt do listy
    void operator+=(MyArray & o);

    //! Dodaje zawartość obiektu do tablicy
    void operator+=(MyArray && o);
};

//! Wypisuje zawartość tablicy
std::ostream & operator<<(std::ostream & out, const MyArray & o);
