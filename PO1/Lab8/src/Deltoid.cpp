#include "Deltoid.h"

Deltoid::Deltoid(const Section & E, const Section & F)
: e(E), f(F)
{
}

Deltoid::Deltoid(const Point & e1, const Point & f1, const Point & e2, const Point & f2)
: e(Section(e1, e2)), f(Section(f1, f2))
{
}

void Deltoid::draw() const
{
    std::cout << "Rysujemy deltoid o wierzchołkach ";
    std::cout << e.getStart() << ", " << f.getStart() << ", ";
    std::cout << e.getEnd() << ", " << f.getEnd() << std::endl;
}

double Deltoid::length() const
{
    Section b1(e.getStart(), f.getStart());
    Section b2(e.getStart(), f.getEnd());
    Section b3(e.getEnd(), f.getStart());
    Section b4(e.getEnd(), f.getEnd());

    return b1.length() + b2.length() + b3.length() + b4.length();
}

void Deltoid::shift(double dx, double dy)
{
    e.shift(dx, dy);
    f.shift(dx, dy);
}

double Deltoid::area() const
{
    return e.length() * f.length() /*/ 2.0*/;
}