#include "Circle.h"

Circle::Circle(const Point & p, double rad): o(p), r(rad)
{
}

void Circle::draw() const
{
    std::cout << "Rysujemy kolo o srodku " << o << " i promieniu " << r << std::endl;
}

double Circle::length() const
{
    return 2 * M_PI * r;
}
    
void Circle::shift(double dx, double dy)
{
    o = Point(o.getX() + dx, o.getY() + dy);
}

double Circle::area() const
{
    return M_PI * r * r;
}
