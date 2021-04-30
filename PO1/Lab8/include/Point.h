#pragma once

#include <iostream>

class Point
{
    friend std::ostream & operator<<(std::ostream & out, const Point & p);
private:
    double x, y;
public:
    Point(double a, double b);

    double getX() const { return x; } 
    double getY() const { return y; }
};

std::ostream & operator<<(std::ostream & out, const Point & p);