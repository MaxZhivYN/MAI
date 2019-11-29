#include <iostream>
#include <cstdlib>

using namespace std;
typedef unsigned long long ull;

template <typename Type>
class MyVector
{
public:
	MyVector(ull index);
	MyVector();
	~MyVector();
	void Push_Back(Type element);
	ull Size();
	void Is_ReSize();
	Type& operator[](ull index);
	Type *mass;
	ull mass_number;
	ull mass_size;
};

template <typename Type>
MyVector<Type>::MyVector(ull index)
{
	mass = new Type[index];
	mass_number = 0;
	mass_size = index;
}

template <typename Type>
MyVector<Type>::MyVector()
{
	mass = new Type[1];
	mass_number = 0;
	mass_size = 1;
}

template <typename Type>
MyVector<Type>::~MyVector()
{
	delete[] mass;
}

template <typename Type>
Type& MyVector<Type>::operator[](ull index)
{
	return mass[index];
}

template <typename Type>
ull MyVector<Type>::Size()
{
	return mass_number;
}

template <typename Type>
void MyVector<Type>::Push_Back(Type element)
{
	Is_ReSize();
	mass[mass_number] = element;
	mass_number++;
}

template <typename Type>
void MyVector<Type>::Is_ReSize()
{
	if (mass_size <= mass_number) {
		mass_size *= 4;
		mass = (Type*)realloc(mass, mass_size * sizeof(Type));
	}
}






