#pragma once

#include <iostream>
#include <cmath>

#include "Base.h"
#include "Point.h"

/**
* Klasa reprezentująca okrąg o środku w punkcie o i promieniu r.
* Dziedziczy po Drawable, Transformable i ClosedShape
*/
class Circle: public ClosedShape
{
private:
    Point o;
    double r;
public:
    Circle(const Point & p, double rad);

    void draw() const override;
    double length() const override;
    void shift(double dx, double dy) override;
    double area() const override;
};