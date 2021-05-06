#pragma once

class Sum
{
private:
    double s=0.0;
public:
    /**
    * Konstruktor ustawiający pole s na x
    * @param x wartość przypisywana polu s
    */
    Sum(double x): s(x) {}

    /**
    * Zwraca wartość pola s
    * @return zwracana wartość s
    */
    double value() const
    {
        return s;
    }

    /**
    * Dodaje x do pola s
    * @param x wartość którą dodajemy do pola s
    */
    void operator()(double x)
    {
        s += x;
    }
};