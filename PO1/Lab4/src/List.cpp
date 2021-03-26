#include "List.h"

void List::insert(int x)
{
    list.push_back(x);
}

void List::print(const char * str) const
{
    std::cout << str << "[ ";
    for (int x: list)
        std::cout << x << " ";
    std::cout << "]\n";
}

int & List::operator[](unsigned i)
{
    if (i < list.size())
    {
        return list[i];
    }
    else
    {
        std::cout << "index out of range\n";
        exit(EXIT_FAILURE);
    }
}

List List::filter(std::function<bool(int)> fun) const
{
    List passed;
    for (int x: list)
    {
        if (fun(x))
            passed.insert(x);
    }

    return passed;
}