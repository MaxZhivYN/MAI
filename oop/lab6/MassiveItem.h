#ifndef MASSIVEITEM_H
#define MASSIVEITEM_H
#include <memory>
#include <iostream>
#include "TAllocationBlock.h"

template<class T> 
class Massive_item {
public:

    Massive_item();
    ~Massive_item();
    std::shared_ptr<T> ptr;
    void* operator new(size_t size);
    void operator delete[](void *ptr);
    static TAllocationBlock mass_allocator;    
};

#include "MassiveItem.cpp"

#endif
