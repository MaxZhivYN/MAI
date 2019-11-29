#include "MassiveItem.h"
#include <iostream>
#include <cstdlib>
#include <memory>


template <class T> 
Massive_item<T>::Massive_item() {}

template <class T>
Massive_item<T>::~Massive_item() {}


template <class T>  
TAllocationBlock Massive_item<T>::mass_allocator(sizeof(Massive_item<T>), 100);


template <class T> 
void* Massive_item<T>::operator new(size_t size) {
    return mass_allocator.allocate();
}


template <class T> 
void Massive_item<T>::operator delete[](void *ptr) {
      mass_allocator.deallocate(ptr);
}

/* #include "Figure.h"
template class Massive_item<Figure>;
template std::ostream& operator<<(std::ostream& os, const Massive_item<Figure>& mass);
*/
