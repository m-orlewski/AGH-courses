#pragma once

#include <iostream>

#include "Operation.h"

class SumOfElements: public Operation
{
private:
    double * numbers = nullptr;
public:
    /**
    * Konstruktor domyślny, przypisuje arr do numbers i n do a
    * @param arr tablica liczb
    * @param n ilość liczb w tablicy arr
    */
    SumOfElements(double * arr, int n): Operation(n)
    {
        numbers = new double[n];
        for (int i=0; i < n; i++)
        {
            numbers[i] = arr[i];
        }
    }

    ~SumOfElements()
    {
        delete [] numbers;
    }

    void print() const override
    {
        std::cout << " " << numbers[0];
        for (int i=1; i < a; i++)
        {
            std::cout << " + " << numbers[i];
        }
    }

    double eval() const override
    {
        double sum = 0.0;
        for (int i=0; i < a; i++)
        {
            sum += numbers[i];
        }
        return sum;
    }
};