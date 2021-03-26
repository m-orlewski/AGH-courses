#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <functional>

class List
{
private:
    std::vector<int> list;
public:
    //! Dodaje x na koniec list
    void insert(int x);

    //! Wypisuje listę w formacie: str [zawartość listy]
    void print(const char * str="") const;

    //! Zwraca referencje do list[i] (błąd gdy i poza zakresem)
    int & operator[](unsigned i);

    //! Zwraca obiekt List zawierający elementy z list dla których fun zwraca true
    List filter(std::function<bool(int)> fun) const;
};