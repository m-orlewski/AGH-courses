#include "Operation.h"

Operation::Operation(int A): a(A)
{
}

void operator>>=(const char * str, const Operation & o)
{
    std::cout << str;
    o.print();
    std::cout << str << std::endl;
}