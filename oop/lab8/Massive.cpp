#include <iostream>
#include <cstdlib>
#include <memory>
#include <algorithm>
#include <thread>
#include <exception>
#include "Massive.h"
#include "TAllocationBlock.h"



template <class T> 
TrMassive<T>::TrMassive() : TrMassive(0) {}


template <class T> 
TrMassive<T>::TrMassive(unsigned int l) 
{
    len = l;
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
bool TrMassive<T>::Empty(){
    return (len == 0);
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
void TrMassive<T>::Delete(int id)
{
    while (!(id >= 0 && id < len)) {
        std::cout << "Imput correct id" << std::endl;
        std::cin >> id;
    }
    data[id].ptr = nullptr;
}

template <class T>
void TrMassive<T>::QS()
{
    int void_cell_id, cmd;
    for (void_cell_id = 0; data[void_cell_id].ptr != nullptr && void_cell_id < Lenght(); ++void_cell_id);
    qs_help(void_cell_id);
    for (void_cell_id = 0; data[void_cell_id].ptr != nullptr && void_cell_id < Lenght(); ++void_cell_id);
    std::cout << "Use threads?" << std::endl;
    std::cout << "1) Yes\n2) No" << std::endl;
    std::cin >> cmd;
    if (cmd == 1) {
        thread_sort(0, void_cell_id - 1);
    }
    else if (cmd == 2) quicksort(0, void_cell_id - 1);
}

template<class T> void TrMassive<T>::thread_sort(int first, int last)
{
  std::packaged_task<void(void) > task(std::bind(std::mem_fn(&TrMassive<T>::sort_parallel), this, first, last)); // создаем задачу для потока
  std::thread th(std::move(task));
  th.join();
  return;
}

template<class T >
std::future<void> TrMassive<T>::sort_in_background(int first, int last) {
    std::packaged_task<void(void) > task(std::bind(std::mem_fn(&TrMassive<T>::sort_parallel), this, first, last)); // создаем задачу для потока
    std::future<void> res(task.get_future()); //оборачиваем ее в future
    std::thread th(std::move(task)); //запускаем поток
    th.detach(); //отсоединяем нити для возможности выйти из функции
    return res;
}
//
template <class T> void TrMassive<T>::sort_parallel(int first, int last) {
  if (first < last){
      int left = first;
      int right = last;
      Massive_item<T> middle = data[(left + right) / 2];
      do
      {
          while (data[left].ptr->Sq() < middle.ptr->Sq()) left++;
          while (data[right].ptr->Sq() > middle.ptr->Sq()) right--;
          if (left <= right)
          {
              Massive_item<T> tmp = data[left];
              data[left] = data[right];
              data[right] = tmp;
              left++;
              right--;
          }
      } while (left <= right);
      // qs(first, right);
      // qs(left, last);

      std::future<void> left_res = this->sort_in_background(first, right);
      std::future<void> right_res = this->sort_in_background(left, last);
      left_res.get();
      right_res.get();
  }
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


//template class TrMassive<Figure>;
