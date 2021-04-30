#include "Point.h"

Point::Point(double a, double b): x(a), y(b)
{
}

std::ostream & operator<<(std::ostream & out, const Point & p)
{
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}