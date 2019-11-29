#include <iostream>
#include <cstdlib>
#include <memory>
#include "Massive.h"
#include "TAllocationBlock.h"


template <class T> 
TrMassive<T>::TrMassive() : TrMassive(0) {}


template <class T> 
TrMassive<T>::TrMassive(unsigned int l) 
{
    len = l;
    if (len > 0) {
        data = new std::shared_ptr<Massive_item<T>>[len];
    }
    for (short int i = 0; i < len; i++){
        data[i] = nullptr;
    }
    std::cout << "massive created!" << std::endl;
}


template <class T> 
TrMassive<T>::TrMassive(const TrMassive<T>& orig) 
{
    len = orig.len;
    data = new std::shared_ptr<Massive_item<T>>[len];
    for(short int i = 0; i < len; i++){
        data[i] = orig.data[i];
    }
    std::cout << "massive copied!" << std::endl;
}


template <class T> 
bool TrMassive<T>::Empty(){
    return (len == 0);
}


template <class T> 
std::shared_ptr<Massive_item<T>>& TrMassive<T>::operator[](const int index)
{
    if (index < 0) {
        std::cout << "Wrong index! Returning element with index '0'!" << '\n';
        return data[0];
    } 
    else if (index >= len) {
        this->Resize(index + 1);
    }
    return data[index];
}


template <class T> 
int TrMassive<T>::Lenght()
{
    return len;
}


template <class T> TrMassive<T>::~TrMassive()
{
    if (len > 0) {
        delete[] data;
        len = 0;
    }
    std::cout << "Massive deleted!" << '\n';
}



template <class T>
void TrMassive<T>::Resize(int l)
{
    if (l > len) {
        std::shared_ptr<Massive_item<T>> *temp = new std::shared_ptr<Massive_item<T>>[l];
		const std::shared_ptr<Massive_item<T>> *pInt = data;
		std::copy(pInt, pInt + len, temp);
		std::swap(temp, data);
	}
    else {
        if (l > 0)
            std::cout << "The number you enter is smaller than the current array size. Enter a different size." << std::endl;
        else
            std::cout << "Enter correct number." << std::endl;
    }
}

template <class A> 
std::ostream& operator<<(std::ostream& os, const TrMassive<A>& mass) 
{
    std::cout << "Massive:" << std::endl;
    std::cout << "Size:" << mass.len << '\n' << "Elements:" << std::endl;
    if (mass.len == 0 ) {
        std::cout << "Empty!" << '\n';
    }
    for (short int i = 0; i < mass.len; i++) {
        std::cout << "[" << i << "]" << ": ";
        if (mass.data[i]->ptr != nullptr) {
            mass.data[i]->ptr->Print();
        } 
        else {
            std::cout << "empty" << std::endl;
        }
    }
    return os;
}


template <class T>
void TrMassive<T>::Delete(int id)
{
    while (!(id >= 0 && id < len)) {
        std::cout << "Imput correct id" << std::endl;
        std::cin >> id;
    }
    data[id]->ptr = nullptr;
}


/* #include "Figure.h"
template class TrMassive<Figure>;
template std::ostream& operator<<(std::ostream& os, const TrMassive<Figure>& mass);
*/
