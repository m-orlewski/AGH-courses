#pragma once

#include <iostream>

class Base
{
    friend std::ostream & operator<<(std::ostream & out, const Base & obj);
protected:
    std::string _name;
public:
    /**
    * Konstruktor domyślny ustawia pole _name na name
    * @param name wartość std::string przypisywana polu _name
    */
    Base(const std::string name): _name(name) {}

    /**
    * Funkcja wirtualna, wypisuje obiekt pochodny klasy Base z odpowiednią ilością wcięć
    * @param out obiekt klasy std::ostream używany do wypisywania
    * @param indent_count ilość wypisanych wcięć
    */
    virtual void print_indented(std::ostream & out, unsigned indent_count) const = 0;

    const std::string & getName() const
    {
        return _name;
    }

    /**
    * Destruktor wirtualny
    */
    virtual ~Base() = default;

};

std::ostream & operator<<(std::ostream & out, const Base & obj);