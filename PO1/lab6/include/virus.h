#pragma once

#include <iostream>
#include <memory>

#include "rna.h"

class Virus
{
protected:
    std::string name;
    std::unique_ptr<RNA> rna;
    unsigned age = 0;
    void operator++(int) { age++; }
public:
    /**
    * Domyślny konstruktor, ustawia pole name na n
    */
    Virus(const std::string & n=""): name(n) {}

    /**
    * Konstruktor kopiujący
    * @param virus kopiowany obiekt
    */
    Virus(Virus & virus): name(virus.name)
    {
        virus++;
        rna = std::make_unique<RNA> (virus.get_RNA()->get_RNA());
    }

    /**
    * Konstruktor przenoszący
    * @param virus obiekt używany do konstrukcji
    */
    Virus(Virus && virus): name(virus.name)
    {
        rna.swap(virus.rna);
        age = virus.age;
        rna->mutate();
    }

    /**
    * Operator przypisania
    * @param virus przypisywany obiekt
    */
    Virus & operator=(Virus & virus)
    {
        name = virus.name;
        rna = std::make_unique<RNA>(virus.get_RNA()->get_RNA());
        age = virus.age;
        return *this;
    }
    /**
    * Zwraca nazwę wirusa
    * @return pole name
    */
    const std::string & get_name() const { return name; }

    /**
    * Zwraca wskaźnik do obiektu klasy RNA
    * @return pole rna
    */
    const RNA * get_RNA() const { return rna.get(); }

    /**
    * Zwraca wiek wirusa
    * @return pole age
    */
    unsigned get_age() const { return age; }

    /**
    * Ustawa łańcuch rna na new_chain
    * @param new_chain
    */
    void set_RNA(const std::vector<Nukleotyp> & new_chain)
    { 
        rna = std::make_unique<RNA> (new_chain);
    }
};