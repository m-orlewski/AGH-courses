#include "Table.h"

void Table::operator+=(const Data & d)
{
    daily_data.push_back(d);
}

void Table::print() const
{
    std::for_each(std::begin(daily_data), std::end(daily_data),
    [](const Data & d)
    {
        d.print();
    });
    std::cout << std::endl;
}

const Table & Table::sort(unsigned col)
{
    for (auto x: daily_data)
    {
        if (col >= x.GetData().size())
        {
            std::cout << "Indeks " << col << " nieprawidlowy!" << std::endl;
            return * this;
        }
    }

    std::sort(std::begin(daily_data), std::end(daily_data),
    [col](const Data & d1, const Data & d2)->bool
    {
        return d1.GetData()[col] < d2.GetData()[col];
    });

    return *this;
}

const Table & Table::sortBy(std::function<bool(const Data &, const Data &)> f)
{
    std::sort(std::begin(daily_data), std::end(daily_data), f);
    return *this;
}