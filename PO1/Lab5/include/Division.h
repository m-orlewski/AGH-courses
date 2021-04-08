#pragma once

#include <iostream>
#include <cstdlib>

#include "Operation.h"

class Division: public Operation
{
private:
    double b;
public:
    /**
    * Konstruktor domyślny, przypisuje wartości A, B składnikom a i b
    * @param A dzielnik
    * @param B dzielna
    */
    Division(int A, double B=1.0): Operation(A), b(B)
    {
        if (b == 0)
        {
            std::cout << "Dzielenie przez 0!\n";
            exit(EXIT_FAILURE);
        }
    }

    void print() const override
    {
        std::cout << " " << a << " / " << b << " ";
    }

    double eval() const override
    {
        return a / b;
    }
};