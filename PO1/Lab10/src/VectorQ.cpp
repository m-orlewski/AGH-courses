#include "VectorQ.h"

void VectorQ::add (std::unique_ptr<Person> person)
{
    queue.push_back(std::move(person));
}

void VectorQ::print(const char * str) const
{
    std::cout << str << std::endl;
    std::for_each(std::begin(queue), std::end(queue), 
    [] (const std::unique_ptr<Person> & person)
    {
        (*person).print();
        std::cout << std::endl;
    });
}

std::vector<Woman *> VectorQ::getWomen()
{
    std::vector<Woman *> women;
    std::for_each(std::begin(queue), std::end(queue),
    [&women] (const std::unique_ptr<Person> & person)
    {
        if (!(*person).is_man())
        {
            women.push_back(dynamic_cast<Woman *>(person.get()));
        }
    });

    return women;
}

void VectorQ::countNames() const
{
    std::map<std::string, int> names;
    std::for_each(std::begin(queue), std::end(queue),
    [&names, this] (const std::unique_ptr<Person> & person)
    {
        if (names.find((*person).name()) == names.end())
        {
            int count = std::count_if(std::begin(this->queue), std::end(this->queue),
            [&person] (const std::unique_ptr<Person> & person2)
            {
                return (*person2).name() == (*person).name();
            });

            names[(*person).name()] = count;
        }
    });

    for (const auto& [key, value] : names)
    {
        std::cout << key << " : " << value << std::endl;
    }
    std::cout << "\n";
}

void VectorQ::haircut(std::string n)
{
    if (n == "")
	{
		(*queue[0]).haircut();
		if ((*queue[0]).done())
		{
			queue.erase(queue.begin());
		}
	}
    else
    {
        auto found = std::find_if(std::begin(queue), std::end(queue),
        [n] (const std::unique_ptr<Person> & person)
        {
            return (*person).name() == n;
        });

        (**found).haircut();
        if ((**found).done())
        {
            queue.erase(found);
        }
    }
}

void VectorQ::shave(std::string n)
{
    if (n == "")
	{
		(*queue[0]).shave();
		if ((*queue[0]).done())
		{
			queue.erase(queue.begin());
		}
	}
	else
    {
        auto found = std::find_if(std::begin(queue), std::end(queue),
        [n] (const std::unique_ptr<Person> & person)
        {
            return (*person).name() == n;
        });

        (**found).shave();
        if ((**found).done())
        {
            queue.erase(found);
        }
    }
}