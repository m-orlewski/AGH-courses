#pragma once

#include "rna.h"

class DNA: public RNA
{
    /**
    * Funkcja zaprzyjaźniona, wypisuje łańcuch dna
    * @param out obiekt klasy ostream służący do wypisywania
    * @param dna wypisywany obiekt
    */
    friend std::ostream & operator<<(std::ostream & out, DNA & dna);
public:

    /**
    * Konstruktor, tworzy obiekt klasy DNA z 2 obiektów klasy RNA
    * @param r1 pierwszy obiekt klasy RNA
    * @param r2 drugi obiekt klasy RNA
    */
    DNA(const RNA & r1, const RNA & r2): RNA({})
    {
        chain = r1.get_RNA();
        for (Nukleotyp x: r2.get_RNA())
            chain.push_back(x);
    }
};

std::ostream & operator<<(std::ostream & out, DNA & dna)
{
    unsigned i;
    for (i=0; i < dna.chain.size() / 2; i++)
    {
        out << static_cast<char>(dna.chain[i]) << " ";
    }
    out << std::endl;
    for (i=0; i < dna.chain.size() / 2; i++)
    {
        out << "| ";
    }
    out << std::endl;
    for (;i < dna.chain.size(); i++)
    {
        out << static_cast<char>(dna.chain[i]) << " ";
    }
    
    return out << std::endl;
}