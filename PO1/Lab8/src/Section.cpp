#include "Section.h"

Section::Section(const Point & A, const Point & B): p1(A), p2(B)
{
}

void Section::draw() const
{
    std::cout << "Rysujemy odcinek od " << p1 << " do " << p2 << std::endl;
}

double Section::length() const
{
    double dx = fabs(p1.getX() - p2.getX());
    double dy = fabs(p1.getY() - p2.getY());

    return sqrt(dx*dx + dy*dy);
}

void Section::shift(double dx, double dy)
{
    p1 = Point(p1.getX() + dx, p1.getY() + dy);
    p2 = Point(p2.getX() + dx, p2.getY() + dy);
}