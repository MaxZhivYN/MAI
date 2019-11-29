#include "MassiveItem.h"
#include <iostream>
#include <cstdlib>
#include <memory>


template <class T> 
Massive_item<T>::Massive_item() {}

template <class T>
Massive_item<T>::~Massive_item() {}


template <class T>  
TAllocationBlock Massive_item<T>::mass_allocator(sizeof(std::shared_ptr<T>), 100);



/* #include "Figure.h"
template class Massive_item<Figure>;
template std::ostream& operator<<(std::ostream& os, const Massive_item<Figure>& mass);
*/
