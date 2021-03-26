#pragma once

#include <iostream>
#include <cmath>
#include <cstdlib>

class ComplexNumber
{
//Funkcje zaprzyjaźnione
    friend std::ostream & operator<<(std::ostream & out, const ComplexNumber & o);
    friend ComplexNumber operator+(double x, const ComplexNumber & o);
private:
    double _x; //część rzeczywista liczby
    double _y; //część urojona liczby
public:
    //! Kontruktor, ustawia _x=x, _y=y
    explicit ComplexNumber(double x, double y=0.0);

    //! Konwerter na double, zwraca _x
    explicit operator double() {return _x;}

    //! Zwraca obiekt ComplexNumber przechowujący sumę 2 liczb zespolonych
    ComplexNumber operator+(const ComplexNumber & o) const;

    //! Zwraca obiekt bedący sumą ComplexNumber i liczby x
    ComplexNumber operator+(double x) const;

    //! Zwraca obiekt będący iloczynem dwóch liczb zespolonych
    ComplexNumber operator*(const ComplexNumber & o) const;

    //! Zwraca obiekt ComplexNumber pomnożony przez x(z przypisaniem)
    ComplexNumber & operator*=(double x);

    //! Zwiększa _x o 1 i zwraca zmieniony obiekt(preinkrementacja)
    ComplexNumber & operator++();

    //! Zwiększa _x o 1 i zwraca obiekt tymczasowy sprzed zmiany(postinkrementacja)
    ComplexNumber operator++(int);

    //! Zwraca obiekt będący różnicą 2 liczb zespolonych
    ComplexNumber operator-(const ComplexNumber & o) const;

    //! Sprawdza czy obiekt this jest mniejszy od obiektu o (porównując moduły)
    bool operator<(const ComplexNumber & o) const;

    //! Zwraca referencje do części rzeczywistej(gdy i=0) lub urojonej(gdy i=1)
    double & operator[](unsigned i);
};

//! Wypisuje liczbe zespoloną w formacie _x + _y*i
std::ostream & operator<<(std::ostream & out, const ComplexNumber & o);

//! Zwraca obiekt bedący sumą ComplexNumber i liczby
ComplexNumber operator+(double x, const ComplexNumber & o);