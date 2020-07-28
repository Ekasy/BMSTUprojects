#include <cstdlib>
#include <cstdio>
#include <locale.h>
#include <iostream>
#include "Vector.h"
#include "VectorIterator.h"
#include "Algorithm.h"
#include <ctime>
#include <string>

template <typename TS>
static TS summa = 0;

template <typename TS>
void add_f(TS i)
{
	summa<TS> = summa<TS> + i;
}

template <typename TS>
class plus
{
private:
	TS my_sum;

public:
	plus<TS>() :my_sum(0)
	{}
	void operator ()(TS i)
	{
		my_sum += i;
	}

	TS getSum() {
		return my_sum;
	}
};

class Student {
private:
	char* name;
	int mark;
public:
	Student() : name(nullptr), mark(0) {}
	Student(const char* mas, int mark)
	{
		name = new char[strlen(mas) + 1];
		strcpy(name, mas);
		this->mark = mark;
	}
	char* Getname() {
		return name;
	}
	Student(const Student& a) {
		name = new char[strlen(a.name) + 1];
		strcpy(name, a.name);
		mark = a.mark;
	}
	~Student() {
		delete[] name;
	}
	bool operator >(Student a) {
		return mark > a.mark;
	}
	const Student& operator = (const Student& cmpObj) {
		if (this == &cmpObj)
			return *this;
		name = new char[strlen(cmpObj.name) + 1];
		strcpy(name, cmpObj.name);
		mark = cmpObj.mark;

		return cmpObj;
	}
	friend std::ostream& operator<<(std::ostream& p_out, const Student& data);
};

std::ostream& operator << (std::ostream& p_out, const Student& data)
{
	p_out << data.name << "  " << data.mark << ".";
	return p_out;
}

int main()
{
	srand(time(NULL));

	char* asdf = new char[4];
	Student stud1("Bob", 8), stud2("Zack", 5), stud3("Sat", 1), stud4("Ann", 6), stud5("Jhon", 4);
	Vector<Student> a({ stud1, stud2, stud3, stud4, stud5 });
	puts("Before sorted");
	for_each(a.begin(), a.end(), [](const Student & a) {
		std::cout << a << std::endl;
		});

	puts("\nAfter sorted");
	Sort(a.begin(), a.end());
	for_each(a.begin(), a.end(), [](const Student & a) {
		std::cout << a << std::endl;
		});

	Vector<int> vec1(5);
	Vector<int>::iterator iter = vec1.begin();
	int i = 0;
	for (auto p = 0; p < 5; ++p) {
		vec1.pushBack(i);
		printf("%d", vec1.at(i));
		++i;
	}
	vec1.at(2) = 10;
	printf("%d", vec1.at(2));
	vec1.at(-1) = 10;

	system("pause");
	return 0;
}