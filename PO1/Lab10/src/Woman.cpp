#include "Persons.h"

Woman::Woman(std::string name, bool haircut, bool makeup)
: Person(name, haircut, false), _makeup(makeup) {}

void Woman::print() const
{
    std::cout << _name << " " << (_haircut ? "nieobcieta" : "obcieta");
    std::cout << " " << (_makeup ? "nieumalowana" : "umalowana");
}

bool Woman::done() const
{
    if (!_haircut && !_makeup)
        return true;
    else
        return false;
} 

void Woman::makeup()
{
    if (_makeup)
        _makeup = false;
    else
        std::cout << "\n!!! Klientka juz umalowana !!!";
}

Woman::~Woman()
{
    print();
    std::cout << " idzie na zakupy\n";
}