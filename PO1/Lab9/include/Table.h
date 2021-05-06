#pragma once

#include "Data.h"

class Table
{
private:
    std::vector<Data> daily_data;
public:
    /**
    * Konstruktor domyślny
    */
    Table() = default;

    /**
    * Operator += dodaje obiekt klasy Data do std::vector daily_data
    * @param d obiekt który jest dodawany na koniec std::vector daily_data
    */
    void operator+= (const Data & d);

    /**
    * Wypisuje nazwy i zawartość obiektów klasy Data z std::vector daily_data 
    * (poprzez wywołanie Data::print())
    */
    void print() const;

    /**
    * Sortuje std::vector daily_data rosnąco po col-tych indeksach wektorów Data::data
    * @param col indeksy elementów po których odbywa sie sortowanie
    * @return posortowany obiekt *this
    */
    const Table & sort(unsigned col);

    /**
    * Sortuje std::vector daily_data używając f jako komparatora
    * @param f funkcja używana jako komparator w sortowaniu
    * @return posortowany obiekt *this
    */
    const Table & sortBy(std::function<bool(const Data &, const Data &)> f);
};