#include "../include/File.h"

File::File(std::string name, unsigned size): Base(name), _size(size) {}

File::File(const File & f): Base(f._name)
{
    _size = f._size;
}

File::~File()
{
    std::cout << "---Destruktor File: " << getName() << std::endl;
}

void File::print_indented(std::ostream & out, unsigned indent_count) const
{
    for (unsigned i=0; i < indent_count; i++)
        out << "\t";
    
    out << _name << " (" << _size << ")\n";
}