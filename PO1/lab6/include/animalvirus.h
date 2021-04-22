#pragma once

#include "virus.h"

class AnimalVirus: public Virus
{
private:
    std::string animal_name = "";
public:
    /**
    * Konstruktor, ustawia pole animal_name na animal_n i wywołuje kontruktor klasy Virus
    */
    AnimalVirus(const std::string & n, 
                            const std::string & animal_n,
                            const std::vector <Nukleotyp> & chain)
                            : Virus(n), animal_name(animal_n)
    {
        rna = std::make_unique<RNA> (chain);
    }
	
	AnimalVirus(): Virus(), animal_name("")
	{
	}
	
	AnimalVirus(AnimalVirus & virus): Virus(virus)
	{
		animal_name = virus.animal_name;
	}
	
	AnimalVirus(AnimalVirus && virus): Virus(std::move(virus))
	{
		animal_name = virus.animal_name;
	}

    /**
    * Operator przypisania, przypisuje obiekt virus
    * @param virus przypisywany obiekt
    * @return zwraca obiekt po przypisaniu
    */
    AnimalVirus & operator=(AnimalVirus  virus)
    {
		dynamic_cast<Virus&>(*this) = virus;
        animal_name = virus.animal_name;
        return *this;
    }

    /**
    * Zwraca pole animal_name
    * @return pole animal_name
    */
    const std::string & get_animal_host() const { return animal_name; }
};