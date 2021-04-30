#pragma once

#include "Base.h"
#include "Section.h"


/**
* Klasa reprezentująca deltoid o przekatnych e i f
* Dziedziczy po Drawable, Transformable i ClosedShape
*/
class Deltoid: public ClosedShape
{
private:
    Section e, f;
public:
    Deltoid(const Section & E, const Section & F);
    Deltoid(const Point & e1, const Point & f1, const Point & e2, const Point & f2);

    void draw() const override;
    double length() const override;
    void shift(double dx, double dy) override;
    double area() const override;
};