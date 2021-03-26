#pragma once

namespace Functors
{
    class DivisibleBy
    {
    private:
        int x;
    public:
        //! Konstruktor ustawia wartość x na X
        DivisibleBy(int X): x(X) {}

        //! Zwraca true jeżeli a jest podzielne prze x, w przeciwnym razie false
        bool operator() (int a)
        {
            return !(a % x);
        }
    };

    class LowerThan
    {
    private:
        int x;
    public:
        //! Konstruktor ustawia wartość x na x
        LowerThan(int X): x(X) {}

        //! Zwraca true jeżeli a jest mniejsze od x, w przeciwnym razie false
        bool operator() (int a)
        {
            return a < x;
        }
    };
}