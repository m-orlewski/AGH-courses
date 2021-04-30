#pragma once

/*
Hierarchia klas:
Bazowe klasy abstrakcyjne: Drawable(metoda wirtualna draw - rysująca kształt) i Transformable(metoda wirtualna shift - dokonująca translacji kształtu)
Klasa ClosedShape - dziedziczy po Drawable i Transformable, również abstrakcyjna(metoda wirtualna area - zwraca pole powierzchni kształtu)
Klasa Point - pomocnicza klasa używana w klasach Circle, Deltoid i Section
Klasy pochodne - Section - dziedziczy po drawable i transformable (reprezentuje odcinek)
                 Circle  - dziedziczy po ClosedShape (reprezentuje okrąg)
                 Deltoid - dziedziczy po ClosedShape (reprezentuje deltoid)
*/

#include "Point.h"
#include "Section.h"
#include "Circle.h"
#include "Deltoid.h"
#include "Base.h"

/**
* Funkcja wywołująca odpowiednią metodę wirtualną metodą draw
* @param to_draw - wskaźnik na obiekt clasy Drawable który należy narysować
*/
void draw(const Drawable * to_draw)
{
    to_draw->draw();
}