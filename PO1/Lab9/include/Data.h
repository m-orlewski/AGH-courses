#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <functional>

#include "Sum.h"

class Data
{
    friend Sum sumData(const Data & d);
private:
    std::string day = "";
    std::vector<double> data;
public:
    /**
    * Konstruktor inicjalizujący pola day i data
    * @param s nazwa dnia przypisywana do pola day
    * @param data wydatki w danym dniu zapisywane w polu data
    */
    Data(const std::string & s, const std::vector<double> & v);

    /**
    * Wypisuje pole day i zawartość std::vector data
    */
    void print() const;

    /**
    * Getter zwracający std::vector data
    * @return stała referencja do std::vector data
    */
    const std::vector<double> & GetData() const;
};

/**
* Zwraca obiekt klasy Sum, utworzony na podstawie obiektu klasy Data
* @param d obiekt klasy Data z którego powstaje obiekt Sum
* @return utworzony obiekt klasy Sum
*/
Sum sumData(const Data & d);