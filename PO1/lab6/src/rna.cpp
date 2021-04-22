#include "rna.h"

std::ostream& operator<<(std::ostream& out, const RNA & seq_)
{ 
    for (char x: seq_.get_RNA())
        out << x << " ";
    return out << std::endl;
}

RNA & RNA::mutate()
{
    chain.push_back(chain[0]);
    chain.erase(chain.begin());

    return *this;
}