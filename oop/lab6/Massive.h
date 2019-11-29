#ifndef MASSIVE_H
#define MASSIVE_H
#include <memory>
#include "TAllocationBlock.h"
#include "MassiveItem.h"

template <class T>
class TrMassive {
public:

    TrMassive();
    TrMassive(unsigned int l);
    TrMassive(const TrMassive<T>& orig);

    bool Empty();
    template <class A> friend std::ostream& operator<<(std::ostream& os, const TrMassive<A>& mass);
    std::shared_ptr<Massive_item<T>>& operator[](const int index);
    int Lenght();
    void Resize(int l);
    void Delete(int id);

    ~TrMassive();
    int len;
private:
    std::shared_ptr<Massive_item<T>> *data;
    
};

#include "Massive.cpp"


#endif
