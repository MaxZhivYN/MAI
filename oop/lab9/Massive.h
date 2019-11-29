#ifndef MASSIVE_H
#define MASSIVE_H
#include <memory>
#include "Iterator.h"

template<class T> class TrMassive {
public:

    TrMassive();
    TrMassive(unsigned int l);
    TrMassive(const TrMassive<T>& orig);

    bool Empty();
    template <class A> friend std::ostream& operator<<(std::ostream& os, const TrMassive<A>& mass);
    std::shared_ptr<T>& operator[](const int index);
    int Lenght();
    void Resize(int l);
    void Delete(int id);

    Iterator<std::shared_ptr<T>, T> begin();
    Iterator<std::shared_ptr<T>, T> end();
    std::shared_ptr<T>* data;
    ~TrMassive();
    int len;
private:
    
    
};

#include "Massive.cpp"

#endif
