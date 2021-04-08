#pragma once

#include <iostream>
#include <cmath>

#include "Operation.h"

class Exponentiation: public Operation
{
private:
    double b;
public:
    /**
    * Konstruktor domyślny, przypisuje wartości A, B składnikom a i b
    * @param A podstawa potęgi
    * @param B wykładnik potęgi
    */
    Exponentiation(int A, double B=1.0): Operation(A), b(B){}

    void print() const override
    {
        std::cout << " " << a << " ^ " << b << " ";
    }

    double eval() const override
    {
        return pow(a, b);
    }
};