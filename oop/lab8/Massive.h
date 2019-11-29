#ifndef MASSIVE_H
#define MASSIVE_H
#include <memory>
#include <future>
#include <functional>
#include "Iterator.h"
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
    std::shared_ptr<T>& operator[](const int index);
    int Lenght();
    void Resize(int l);
    void Delete(int id);
    void QS();
    void quicksort(int first, int last);
    void thread_sort(int first, int last);
    std::future<void> sort_in_background(int first, int last);
    void sort_parallel(int first, int last);
    Iterator<Massive_item<T>, T> begin();
    Iterator<Massive_item<T>, T> end();

    ~TrMassive();
private:
    int len;
    Massive_item<T>  *data;
    
    void qs_help(int id_now);
};

#include "Massive.cpp"


#endif
