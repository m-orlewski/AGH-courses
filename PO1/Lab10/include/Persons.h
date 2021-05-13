#pragma once

#include "Person.h"

class Man: public Person
{
private:
    bool _shave;
public:
    Man(std::string name, bool haircut=true, bool shave=true);

    void print() const override;

    bool done() const override;

    void shave() override;

    void makeup() override {}

    ~Man();
};

class Woman: public Person
{
private:
    bool _makeup;
public:
    Woman(std::string name, bool haircut=true, bool makeup=true);

    void print() const override;

    bool done() const override;

    void makeup() override;

    void shave() override {}

    ~Woman();
};