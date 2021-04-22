#pragma once

#include <iostream>
#include <vector>
#include <typeinfo>

#include "Base.h"
#include "File.h"

class Dir: public Base
{
private:
    std::vector<Base *> sub_folders;
	void deep_copy(Dir * folder);
public:
    /**
    * Konstruktor domyślny, wywołuje konstruktor domyślny klasy Base
    * @param name parametr name przekazywany do konstruktora Base
    */
    Dir(std::string name="");

    Dir(const Dir & dir);

    ~Dir();

    /**
    * Operator += dodający wskaźnik na Base do sub_folders
    * @param sub_folder dodawany wskaźnik klasy Base
    */
    void operator+= (Base * sub_folder);

    void print_indented(std::ostream & out, unsigned indent_count) const override;

    Dir * getDir(std::string name) const;

    void copy(Dir * folder);

    void copy(File * folder);

    File * get(std::string name) const;

    void operator-=(std::string name);
};