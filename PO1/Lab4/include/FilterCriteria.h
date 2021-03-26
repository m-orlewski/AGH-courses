#pragma once

#include <vector>
#include <functional>
#include <cstdlib>
#include <iostream>

class FilterCriteria
{
private:
    std::vector<std::function<bool(int)>> criterias;
public:
    //! Dodaje fun do criterias
    void add(std::function<bool(int)> fun);

    //! Zwraca rozmiar criterias
    int size() const;

    //! Zwraca i-ty element z criterias
    std::function<bool(int)> get(unsigned i) const;
};