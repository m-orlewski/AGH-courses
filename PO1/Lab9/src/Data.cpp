#include "Data.h"

Data::Data(const std::string & s, const std::vector<double> & v) : day(s), data(v) {}

void Data::print() const
{
    std::cout << day << ":";
    for (auto x: data)
        std::cout << std::setw(5) << x << " ";
    std::cout << std::endl;
}

Sum sumData(const Data & d)
{
    return Sum(std::accumulate(std::begin(d.data), std::end(d.data), 0.0));
}

const std::vector<double> & Data::GetData() const
{
    return data;
}