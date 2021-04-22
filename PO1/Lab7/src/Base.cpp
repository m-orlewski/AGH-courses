#include "../include/Base.h"

std::ostream & operator<<(std::ostream & out, const Base & obj)
{
    obj.print_indented(out, 0);
    return out;
}