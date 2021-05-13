#include "Persons.h"

Man::Man(std::string name, bool haircut, bool shave)
: Person(name, haircut), _shave(shave) {}

void Man::print() const
{
    std::cout << _name << " " << (_haircut ? "nieobciety" : "obciety");
    std::cout << " " << (_shave ? "nieogolony" : "ogolony");
}

bool Man::done() const
{
    if (!_haircut && !_shave)
        return true;
    else
        return false;
}

void Man::shave()
{
    if (_shave)
        _shave = false;
    else
        std::cout << "\n!!! Klient juz ogolony !!!";
}

Man::~Man()
{
    print();
    std::cout << " idzie na piwko\n";
}