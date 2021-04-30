#pragma once

#include <cmath>

#include "Base.h"
#include "Point.h"

/**
* Klasa reprezentująca odcinek o początku i końcu w punktach p1 i p2
* Dziedziczy po Drawable i Transformable
*/
class Section: public Drawable, public Transformable
{
private:
    Point p1, p2;
public:
    Section(const Point & A, const Point & B);

    const Point & getStart() const { return p1; }
    const Point & getEnd() const { return p2; }

    void draw() const override;
    double length() const override;
    void shift(double dx, double dy) override;
};