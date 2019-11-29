#include <iostream>
#include <cstdlib>
#include <memory>
#include "Massive.h"
#include "TAllocationBlock.h"


template <class T> 
TrMassive<T>::TrMassive() : TrMassive(5) {}


template <class T> 
TrMassive<T>::TrMassive(unsigned int l) 
{
    len = l;
    number = 0;
    if (len > 0) {
        data = new Massive_item<T>[len];
    }
    for (short int i = 0; i < len; i++){
        data[i].ptr = nullptr;
    }
    std::cout << "massive created!" << std::endl;
}


template <class T> 
TrMassive<T>::TrMassive(const TrMassive<T>& orig) 
{
    len = orig.len;
    data = new TrMassive<T>[len];
    for(short int i = 0; i < len; i++){
        data[i] = orig.data[i];
    }
    std::cout << "massive copied!" << std::endl;
}


template <class T> 
bool TrMassive<T>::Empty()
{
    return (len == 0);
}

template <class T>
bool TrMassive<T>::Is_full()
{
    return (number == 5);
}


template <class T> 
std::shared_ptr<T>& TrMassive<T>::operator[](const int index)
{
    if (index < 0) {
        std::cout << "Wrong index! Returning element with index '0'!" << '\n';
        return data[0].ptr;
    } 
    else if (index >= len) {
        this->Resize(index + 1);
    }
    return data[index].ptr;
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
Iterator<Massive_item<T>, T> TrMassive<T>::begin() 
{
    return Iterator<Massive_item<T>, T>(data, 0);
}


template <class T> 
Iterator<Massive_item<T>, T> TrMassive<T>::end()
{
    return Iterator<Massive_item<T>, T>(data, len);
}

template <class T> 
void TrMassive<T>::Resize(int l)
{
    if (l > len) {
		Massive_item<T> *temp = new Massive_item<T>[l];
		const Massive_item<T> *pInt = data;
		std::copy(pInt, pInt + len, temp);
		std::swap(temp, data);
        len = l;
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
        if (mass.data[i].ptr != nullptr) {
            mass.data[i].ptr->Print();
        } 
        else {
            std::cout << "empty" << std::endl;
        }
    }
    return os;
}


template <class T>
void TrMassive<T>::QS()
{
    int void_cell_id, cmd;
    for (void_cell_id = 0; data[void_cell_id].ptr != nullptr && void_cell_id < Lenght(); ++void_cell_id);
    qs_help(void_cell_id);
    for (void_cell_id = 0; data[void_cell_id].ptr != nullptr && void_cell_id < Lenght(); ++void_cell_id);
    if (void_cell_id > 0) 
        quicksort(0, void_cell_id - 1);
}


template <class T>
void TrMassive<T>::quicksort(int first, int last)
{
	Massive_item<T> mid;
	int f = first, l = last;
	mid = data[(f + l) / 2]; //вычисление опорного элемента
    do {
        while (data[f].ptr->Sq() < mid.ptr->Sq()) f++;
        while (data[l].ptr->Sq() > mid.ptr->Sq()) l--;
        if (f <= l) { //перестановка элементов
            std::swap(data[l], data[f]);
            f++;
            l--;
        }
    } while (f < l);
    if (first < l) quicksort(first, l);
    if (f < last) quicksort(f, last);
}


template <class T>
void TrMassive<T>::qs_help(int id_now)
{
    int void_cell_id = id_now;
    for (id_now; data[id_now].ptr == nullptr && id_now < Lenght(); ++id_now);
    int employed_cell_id = id_now;
    if (employed_cell_id == Lenght()) return;
    std::swap(data[void_cell_id], data[employed_cell_id]);
    qs_help(void_cell_id + 1);
}


template <class T>
bool TrMassive<T>::Insert_to_cell(std::shared_ptr<Figure> figure)
{
    if (Is_full()) return false;
    data[number].ptr = figure;
    number++;
    QS();
    return true;
}


template <class T>
void TrMassive<T>::Delete(int id)
{
    while (!(id >= 0 && id < len)) {
        std::cout << "Imput correct id" << std::endl;
        std::cin >> id;
    }
    data[id].ptr = nullptr;
}


/* #include "Figure.h"
template class TrMassive<Figure>;
template std::ostream& operator<<(std::ostream& os, const TrMassive<Figure>& mass);
*/
