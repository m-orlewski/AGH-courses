#include "FilterCriteria.h"

void FilterCriteria::add(std::function<bool(int)> fun)
{
    criterias.push_back(fun);
}

int FilterCriteria::size() const
{
    return criterias.size();
}

std::function<bool(int)> FilterCriteria::get(unsigned i) const
{
    if (i < criterias.size())
    {
        return criterias[i];
    }
    else
    {
        std::cout << "index out of range\n";
        exit(EXIT_FAILURE);
    }
}

