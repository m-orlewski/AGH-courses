#pragma once

#include <iostream>

template <typename T>
struct Node
{
	T value;
	Node<T>* next = nullptr;
	Node<T>* prev = nullptr;
	
	friend std::ostream& operator<< (std::ostream& out, const Node& node)
	{
		return out << node.value;
	}
	
	void append(std::string s)
	{
		value += s;
	}
};

