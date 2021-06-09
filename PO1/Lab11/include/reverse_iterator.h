#pragma once

#include "node.h"

template <typename T>
class ReverseIterator
{
public:
	using value_type = Node<T>;
	using pointer = Node<T>*;
	using reference = Node<T>&;
	
	ReverseIterator(pointer p) : ptr(p) {}
	
	reference operator* () const { return *ptr; }
	pointer operator-> () { return ptr; }
	
	ReverseIterator& operator++ ()
	{
		ptr = ptr->prev;
		return *this;
	}
	
	friend bool operator== (const ReverseIterator& it1, const ReverseIterator& it2)
	{
		return it1.ptr == it2.ptr;
	}
	
	friend bool operator!= (const ReverseIterator& it1, const ReverseIterator& it2)
	{
		return it1.ptr != it2.ptr;
	}
private:
	pointer ptr;
};