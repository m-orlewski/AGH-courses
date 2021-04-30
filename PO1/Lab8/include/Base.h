#pragma once

/**
* Klasa abstrakcyjna posiadające wirtualne metody draw() - rysuje kształ na ekranie,
* length() - zwraca długość/obwód kształtu
*/
class Drawable
{
public:
    virtual void draw() const = 0;
    virtual double length() const = 0;
};

/**
* Klasa abstrakcyjna posiadająca wirtualną metodą shift(dx, dy) - dokonuje translacji
* kształtu o wektro [dx, dy]
*/
class Transformable
{
public:
    virtual void shift(double dx, double dy) = 0;
};

/**
* Klasa abstrakcyjna posiadająca wirtualną metodą area() - zwraca pole powierzchni kształtu
*/
class ClosedShape: public Drawable, public Transformable
{
public:
    virtual double area() const = 0;
};