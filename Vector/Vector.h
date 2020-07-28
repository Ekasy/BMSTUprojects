#pragma once
#include <cstdlib>
#include <cstdio>
#include <locale.h>
#include <iostream>
#include "exception.h"

template<typename T>
class VectorIterator;

template <typename T>
class Vector
{
private:
	int my_capacity;
	int my_size;
	T* vec;

public:
	typedef VectorIterator<T> iterator;

	Vector() :my_size(0), my_capacity(0), vec(nullptr)		//конструктор по умолчанию
	{}

	explicit Vector(int my_size)			//конструктор принимающий количество элементов
	{
		//this->my_size = my_size;
		this->my_size = 0;
		this->my_capacity = 2*my_size;
		this->vec = new T[my_capacity];
		//for (int i = 0; i < my_size; ++i)
			//vec[i] = 0;
	}
	Vector(int my_size, T value)	//конструктор, принимающий количество элементов,
									//и значение, инициализирующее элементы массива
	{
		this->my_size = my_size;
		this->my_capacity = my_size;
		this->vec = new T[my_capacity];
		for (int i = 0; i < this->my_size; ++i) {
			this->vec[i] = value + i;
			//std::cin >> vec[i];
		}
	}
	template<class Iter>
	Vector(Iter iter_beg, Iter iter_end)	//конструктор, принимающий интервал,
																		//заданный итераторами
	{
		for (Iter iter_tmp = iter_beg; iter_tmp < iter_end; ++iter_tmp) {
			pushBack(*iter_tmp);
		}
	}

	Vector(const std::initializer_list<T>& list)			//конструктор, принимающий список инициализации
	{
		my_size = list.size();
		my_capacity = list.size() + 2;
		vec = new T[my_capacity];
		int count = 0;
		for (auto p = list.begin(); p != list.end(); ++p) {
			vec[count] = *p;
			count++;
		}
	}

	Vector(const Vector& p_vec)			//конструктор копирования
	{
		this->my_size = p_vec.my_size;
		this->my_capacity = p_vec.my_capacity;
		this->vec = new T[this->my_size];
		for (int i = 0; i < this->my_size; ++i)
			this->vec[i] = p_vec.vec[i];
	}

	Vector(Vector&& p_vec)			//конструктор переноса
	: my_size(p_vec.my_size), my_capacity(p_vec.my_capacity), vec(p_vec.vec)
	{
		p_vec.my_size = 0;
		p_vec.my_capacity = 0;
		p_vec.vec = nullptr;
	}

	Vector& operator = (const Vector& p_vec)		//оператор присваивания с копированием
	{
		if (this == &p_vec)
			return *this;

		delete[] this->vec;
		this->my_size = p_vec.my_size;
		this->my_capacity = p_vec.my_capacity;
		this->vec = new T[this->my_size];
		for (int i = 0; i < this->my_size; ++i)
			this->vec[i] = p_vec.vec[i];
		return *this;
	}

	Vector& operator = (Vector&& p_vec)			//оператор присваивания с переносом
	{
		delete[] this->vec;
		this->vec = p_vec.vec;
		this->my_capacity = p_vec.my_capacity;
		this->my_size = p_vec.my_size;
		p_vec.vec = nullptr;
		p_vec.my_size = 0;
		p_vec.my_capacity = 0;
		return *this;
	}

	Vector& operator [] (int i)
	{
		return vec[i];
	}

	const Vector& operator [] (int i) const
	{
		return vec[i];
	}

	T& at(int idx)
	{
		try {
			if (idx < 0 || idx >= this->my_size)
			{
				throw cls_OutOfRangeException(idx, my_size);
			}
		}
		catch (cls_OutOfRangeException e) {
			std::cerr << e.what();
		}
		return vec[idx];
	}

	const T& at(int idx) const
	{
		if (idx < 0 || idx >= my_size)
		{
			throw cls_OutOfRangeException(idx, my_size);
		}
		return vec[idx];
	}

	iterator begin()
	{
		return iterator(this->vec);
	}

	iterator end()
	{
		return iterator(this->vec + my_size);
	}

	void pushBack(const T& elem)
	{
		if (my_size >= my_capacity)
			reserve(2 * my_capacity);
		this->vec[my_size++] = elem;
	}

	void popBack()
	{
		this->my_size--;
	}

	int insert(iterator pos, T elem) {
		if (my_size + 1 <= my_capacity)
			my_size++;
		else {
			this->reserve(2 * my_capacity);
		}
		VectorIterator<T> ptr(this->end());
		int count = 0;
		while (ptr > pos) {
			*ptr.current = *(ptr.current - 1);
			--ptr;
			count++;
		}
		*pos.current = elem;
		return my_size - count;
	}

	T insert(iterator pos, iterator beg, iterator end) {
		if (beg == end || !beg.current || !end.current)
			return *pos;
		VectorIterator<T> p = beg;
		int countb = 0;
		end--;
		while (p != end) {
			countb++;
			p++;
		}
		countb++;
		int countp = 0;
		p = pos;
		while (begin() != p) {
			countp++;
			p--;
		}
		T* mas = new T[countb + my_size];
		p = begin();
		for (int i = 0; i < countp; i++) {
			mas[i] = *p;
			p++;
		}
		for (int i = countp; i < countp + countb; i++) {
			mas[i] = *beg;
			beg++;
		}
		for (int i = countp + countb; i < my_size + countb; i++) {
			mas[i] = *pos;
			pos++;
		}
		delete[] vec;
		vec = new T[countb + my_size];
		my_size = countb + my_size;
		for (int i = 0; i < my_size; i++)
			vec[i] = mas[i];
		my_capacity = my_size + 2;
		delete[] mas;
		return *vec;
	}

	int erase(iterator pos) {	
		int count = 0;
		while (begin() != pos) {
			count++;
			pos--;
		}
		for (int i = count; i < my_size; i++)
			vec[i] = vec[i + 1];
		my_size--;
		return count;
	}

	void reserve(int p_my_capacity)
	{
		if (this->vec == nullptr)
		{
			this->my_capacity = 0;
			this->my_size = 0;
		}

		T* new_vec = new T[p_my_capacity];
		int l_size = p_my_capacity < this->my_size ? p_my_capacity : my_size;

		for (int i = 0; i < l_size; ++i)
			new_vec[i] = this->vec[i];

		this->my_capacity = p_my_capacity;
		delete[] this->vec;
		this->vec = new_vec;
	}

	void resize(int num)
	{
		reserve(num);
		this->my_size = num;
	}

	bool empty() const
	{
		return my_size == 0;
	}

	int size() const
	{
		return my_size;
	}

	int capacity() const
	{
		return my_capacity;
	}

	void clear() const
	{
		if (this->vec != nullptr)
			delete[] this->vec;
		this->vec = nullptr;
		this->my_capacity = 0;
		this->my_size = 0;
	}

	void show()
	{
		for (int i = 0; i < this->my_size; ++i)
			std::cout << this->vec[i] << " ";
	}

	~Vector()
	{
		delete[] vec;
	}
};