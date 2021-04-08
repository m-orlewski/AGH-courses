#pragma once

#include <iostream>
#include <cstring>

class Operation
{
    friend void operator>>=(const char * str, const Operation & o);
protected:
    int a;
public:
    /**
    * Konstruktor przypisujący wartość A do a
    * @param A przypisywana wartość
    */
    Operation(int A=0);

    /**
    * Destruktor wirtualny
    */
    virtual ~Operation() {}

    /** 
    * Metoda polimorficzna, wypisuje operacje matematyczną jaką wykonuje obiekt
    */
    virtual void print() const = 0;

    /** 
    * Metoda polimorficzna, wylicza wartość operacji matematycznej jaką wykonuje obiekt
    * @return zwraca wartość wyliczonej operacji matematycznej
    */
    virtual double eval() const = 0;

};

/**
* Wypisuje operacje arytmetyczną w formacie str <operacja> str
* @param str używany w wypisywaniu
* @param o obiekt reprezentujący operacje
*/
void operator>>=(const char * str, const Operation & o);