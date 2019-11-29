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
private:
    static TAllocationBlock mass_allocator;
    
};

#include "MassiveItem.cpp"

#endif
