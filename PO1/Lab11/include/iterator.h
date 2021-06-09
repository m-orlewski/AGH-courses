#pragma once

#include "node.h"

template <typename T>
class Iterator
{
public:
	using value_type = Node<T>;
	using pointer = Node<T>*;
	using reference = Node<T>&;
	
	Iterator(pointer p) : ptr(p) {}
	
	reference operator* () const { return *ptr; }
	pointer operator-> () { return ptr; }
	
	Iterator& operator++ ()
	{
		ptr = ptr->next;
		return *this;
	}
	
	friend bool operator== (const Iterator& it1, const Iterator& it2)
	{
		return it1.ptr == it2.ptr;
	}
	
	friend bool operator!= (const Iterator& it1, const Iterator& it2)
	{
		return it1.ptr != it2.ptr;
	}
private:
	pointer ptr;
};