#pragma once

#include <iostream>

#include "node.h"
#include "iterator.h"
#include "reverse_iterator.h"

template <typename T>
class List
{
	friend std::ostream& operator<< (std::ostream& out, const List& list)
	{
		Node<T>* ptr = list.head;
		out << "{";
		while (ptr)
		{
			out << "\"" << ptr->value << "\"";
			ptr = ptr->next;
			if (ptr)
				out << ", ";
			
		}
		return out << "}";
	}
	
private:
	Node<T>* head = nullptr;
public:
	List() {}
	List (int n, const T* arr);
	List(const List<T>& list);
	void push_back(T val);
	void pop_back();
	T& front();
	~List();
	
	Iterator<T> begin();
	Iterator<T> end();
	
	ReverseIterator<T> rbegin();
	ReverseIterator<T> rend();
};

template <typename T>
List<T>::List (int n, const T* arr)
{
	head = new Node<T>;
	head->value = arr[0];
	Node<T>* ptr = head->next;
	Node<T>* prev = head;
	for (int i=1; i < n; i++)
	{
		ptr = new Node<T>;
		ptr->value = arr[i];
		ptr->prev = prev;
		prev->next = ptr;
		prev = ptr;
		ptr = ptr->next;
	}
}

template <typename T>
List<T>::List(const List<T>& list) : head(new Node<T>)
{
	head->value = list.head->value;
	Node<T>* ptr = list.head->next;
	Node<T>* prev = head;
	Node<T>* ptr2 = head->next;
	while (ptr)
	{
		ptr2 = new Node<T>;
		ptr2->value = ptr->value;
		ptr2->prev = prev;
		prev->next = ptr2;
		
		prev = ptr2;
		ptr2 = ptr2->next;
		ptr = ptr->next;
	}
}

template <typename T>
void List<T>::push_back(T val)
{
	if (!head)
	{
		head = new Node<T>;
		head->value = val;
	}
	else
	{
		Node<T>* ptr = head;
		Node<T>* prev = nullptr;
		while (ptr)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		ptr = new Node<T>;
		ptr->value = val;
		ptr->prev = prev;
		prev->next = ptr;
	}
}

template <typename T>
void List<T>::pop_back()
{
	Node<T>* ptr = head;
	Node<T>* prev = nullptr;
	
	while (ptr->next)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	
	delete ptr;
	
	if (prev)
		prev->next = nullptr;
	else
		head = nullptr;
}

template <typename T>
T& List<T>::front()
{
	return head->value;
}

template <typename T>
List<T>::~List()
{
	Node<T>* ptr = head;
	Node<T>* temp;
	
	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		
		delete temp;
	}
}

template <typename T>
Iterator<T> List<T>::begin()
{
	return Iterator(head);
}

template <typename T>
Iterator<T> List<T>::end()
{
	Node<T>* ptr = head;
	if (!ptr)
		return Iterator(head);
	
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	return Iterator(ptr->next);
}

template <typename T>
ReverseIterator<T> List<T>::rbegin()
{
	Node<T>* ptr = head;
	if (!ptr)
		return ReverseIterator(head);
	
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	return ReverseIterator(ptr);
}

template <typename T>
ReverseIterator<T> List<T>::rend()
{
	return ReverseIterator(head->prev);
}




