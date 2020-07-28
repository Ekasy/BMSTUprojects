#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
#include "Vector.h"
//#include "VectorIterator.h"

template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt beg, InputIt end, UnaryFunction op)
{
	for (; beg != end; ++beg) {
		op(*beg);
	}
	return op;
}

template<class InputIt, class UnaryPredicate>
auto find_if(InputIt beg, InputIt end, UnaryPredicate pred)
{
	for (; beg != end; ++beg) {
		if (pred(*beg)) {
			return beg;
		}
	}
	end--;
	return end;
}

template<class ForwardIt>
auto min_element(ForwardIt beg, ForwardIt end)
{
	if (beg == end) return 0;

	auto smallest = *beg;
	for (; beg != end; ++beg) {
		if (*beg < smallest) {
			smallest = *beg;
		}
	}
	return smallest;
}

template<class ForwardIt>
auto max_element(ForwardIt beg, ForwardIt end)
{
	if (beg == end) return 0;
	auto largest = *beg;
	++beg;
	for (; beg != end; ++beg) {
		if (largest < *beg) {
			largest = *beg;
		}
	}
	return largest;
}

template < class _Type >
void Sort(_Type begin, _Type end)
{ 
	for (auto i = begin; i != end; ++i)
		for (auto j = i; j != end; ++j) {
			if (*i > *j) {
				auto buf = *i;
				*i = *j;
				*j = buf;
			}
		}
}

template<class InputIt, class OutputIt, class UnaryPredicate>
OutputIt copy_if(InputIt sourceBeg, InputIt sourceEnd, OutputIt destBeg, UnaryPredicate pred)
{

	int i = 0;
	while (sourceBeg != sourceEnd) {
		if (pred(*sourceBeg)) {
			*destBeg = *sourceBeg;
			destBeg++;
			i = 1;
		}
		sourceBeg++;
	}
	if (i == 0)
		exit(0);
	else {
		return destBeg;
	}
}

template<class InputIt>
auto sum(InputIt beg, InputIt end)
{
	auto summa = *beg;
	summa = summa - *beg;
	for (auto i = beg; i < end; ++i) {
		summa = summa + *i;
	}
	return summa;
}