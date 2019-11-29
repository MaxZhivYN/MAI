#ifndef MASSIVE_H
#define MASSIVE_H
#include <memory>
#include "Iterator.h"
#include "TAllocationBlock.h"
#include "MassiveItem.h"
#include "Figure.h"

template <class T>
class TrMassive {
public:

    TrMassive();
    TrMassive(unsigned int l);
    TrMassive(const TrMassive<T>& orig);

    bool Empty();
    bool Is_full();
    template <class A> friend std::ostream& operator<<(std::ostream& os, const TrMassive<A>& mass);
    std::shared_ptr<T>& operator[](const int index);
    int Lenght();
    void Resize(int l);
    void Delete(int id);
    void quicksort(int first, int last);
    void qs_help(int id_now);
    void QS();
    Iterator<Massive_item<T>, T> begin();
    Iterator<Massive_item<T>, T> end();
    bool Insert_to_cell(std::shared_ptr<Figure> figure);
    ~TrMassive();
    int len;
    int number;
    Massive_item<T>  *data;
private:
    
    static TAllocationBlock mass_allocator;
    
    
};

#include "Massive.cpp"


#endif
