#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <map>
#include <typeinfo>

#include "Person.h"
#include "Persons.h"

class VectorQ
{
private:
    std::vector<std::unique_ptr<Person>> queue;
public:
    void add (std::unique_ptr<Person> person);

    void print(const char * str) const;

    std::vector<Woman *> getWomen();

    void countNames() const;

    void haircut(std::string n="");

    void shave(std::string n="");
};