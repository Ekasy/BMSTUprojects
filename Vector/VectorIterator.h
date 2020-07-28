#pragma once
#include <cstdlib>
#include <cstdio>
#include <locale.h>
#include <iostream>
//#include "exception.h"

template<typename T>
class VectorIterator
{
private:


public:
	T* current;
	typedef VectorIterator iterator;

	VectorIterator<T>(T* curr) : current(curr)
	{}

	VectorIterator<T>(const VectorIterator& p_curr)
	{
		current = p_curr.current;
	}

	iterator operator + (int n)
	{
		current = current + n;
		return current;
	}
	iterator operator - (int n)
	{
		current = current - n;
		return current;
	}

	iterator operator ++ (int) 
	{ 
		iterator buffer(*this);
		current++;
		return buffer;
	}

	iterator operator -- (int) {
		iterator buffer(current);
		current--;
		return buffer; 
	}
	iterator operator ++ () { 
		current++;
		return *this; 
	}

	iterator operator -- () {
		current--;
		return *this;
	}

	iterator operator += (int n)
	{
		current = current + n;
		return current;
	}
	iterator operator -= (int n)
	{
		current = current - n;
		return current;
	}

	operator T* () { return current; }
	T& operator -> () { return current; }

	VectorIterator<T>& operator = (const VectorIterator & other)
	{
		if (this != &other)
			current = other.current;
		return *this;
	}

	bool operator == (const VectorIterator & other) { return current == other.current; }
	bool operator != (const VectorIterator & other) { return current != other.current; }
	bool operator < (const VectorIterator & other) { return current < other.current; }
	bool operator <= (const VectorIterator & other) { return current <= other.current; }
	bool operator > (const VectorIterator & other) { return current > other.current; }
	bool operator >= (const VectorIterator & other) { return current >= other.current; }
};