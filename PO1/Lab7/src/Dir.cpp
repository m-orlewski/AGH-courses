#include "../include/Dir.h"

Dir::Dir(std::string name): Base(name) {}

Dir::Dir(const Dir & dir): Base(dir._name)
{
    for(auto x: dir.sub_folders)
    {
        sub_folders.push_back(new Dir(dynamic_cast<Dir &>(*x)));
    }
}

Dir::~Dir()
{
    std::cout << "Destruktor Dir: " << _name << std::endl;
    for (unsigned i=0; i < sub_folders.size(); i++)
    {
        delete sub_folders[i];
    }
}

void Dir::operator+=(Base * sub_folder)
{
    sub_folders.push_back(sub_folder);
}

void Dir::print_indented(std::ostream & out, unsigned indent_count) const
{
    for (unsigned i=0; i < indent_count; i++)
        out << "\t";
    
    out << _name << " (dir)\n";

    for (auto folder: sub_folders)
    {
        folder->print_indented(out, indent_count + 1);
    }
}

Dir * Dir::getDir(std::string name) const
{
    for (auto folder: sub_folders)
    {
        if (folder->getName() == name && typeid(*folder) == typeid(Dir))
        {
            return dynamic_cast<Dir *>(folder);
        }
    }

    return nullptr;
}

void Dir::copy(Dir * folder)
{
	sub_folders.push_back(new Dir(*folder));
	for (auto x: folder->sub_folders)
	{
		if (typeid(*x) == typeid(File))
		{
			sub_folders[sub_folders.size()-1]->sub_folders->copy(dynamic_cast<File &>(*x));
		}
		else
		{
			sub_folders[sub_folders.size()-1]->sub_folders->copy(dynamic_cast<Dir &>(*x));
		}
	}
}

void Dir::copy(File * folder)
{
    sub_folders.push_back(new File(*folder));
}

File * Dir::get(std::string name) const
{
    for (auto folder: sub_folders)
    {
        if (folder->getName() == name && typeid(*folder) == typeid(File))
        {
            return dynamic_cast<File *>(folder);
        }
    }

    return nullptr;
}

void Dir::operator-=(std::string name)
{
    for (unsigned i=0; i < sub_folders.size(); i++)
    {
        if (sub_folders[i]->getName() == name)
        {
            delete sub_folders[i];
            sub_folders.erase(sub_folders.begin() + i);
        }
    }
}