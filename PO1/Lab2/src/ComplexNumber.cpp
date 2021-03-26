#include "../include/ComplexNumber.h"


ComplexNumber::ComplexNumber(double x, double y): _x(x), _y(y)
{
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber & o) const
{
    return ComplexNumber(_x+o._x, _y+o._y);
}

ComplexNumber ComplexNumber::operator+(double x) const
{
    return ComplexNumber(_x + x, _y);
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber & o) const
{
    return ComplexNumber(_x * o._x - _y * o._y, _x * o._y + _y * o._x);
}

ComplexNumber & ComplexNumber::operator*=(double x)
{
    _x *= x;
    _y *= x;

    return *this;
}

ComplexNumber & ComplexNumber::operator++()
{
    _x++;

    return *this;
}

ComplexNumber ComplexNumber::operator++(int)
{
    ComplexNumber temp(_x, _y);
    _x++;

    return temp;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber & o) const
{
    return ComplexNumber(_x - o._x, _y - o._y);
}

bool ComplexNumber::operator<(const ComplexNumber & o) const
{
    return (sqrt(_x*_x + _y*_y) < sqrt(o._x*o._x + o._y*o._y));
}

double & ComplexNumber::operator[](unsigned i)
{
    if (i == 0)
    {
        return _x;
    }
    else if (i == 1)
    {
        return _y;
    }
    else
    {
        std::cout << "Subscript out of range, has to be 0 or 1\n";
        exit(EXIT_FAILURE);
    }
}

std::ostream & operator<<(std::ostream & out, const ComplexNumber & o)
{
    out << o._x << " + " << o._y << "i";
    return out;
}

ComplexNumber operator+(double x, const ComplexNumber & o)
{
    return o + x;
}