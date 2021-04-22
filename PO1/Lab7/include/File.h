#pragma once

#include <iostream>

#include "Base.h"

class File: public Base
{
private:
    unsigned _size;
public:
    File(std::string name="", unsigned size=0);

    File(const File & f);

    ~File();

    void print_indented(std::ostream & out, unsigned indent_count) const override;
};