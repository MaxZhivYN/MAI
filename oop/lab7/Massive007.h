#ifndef MASSIVE007_H
#define MASSIVE007_H
#include <memory>
#include "Figure.h"
#include "Massive.h"


class Massive {
public:

    Massive();

    friend std::ostream& operator<<(std::ostream& os, const Massive& mass);
    std::shared_ptr<TrMassive<Figure>> operator[](int index);
    void Resize(int l);
    void Delete(int id);
    int Lenght();
    void Insert(std::shared_ptr<Figure> figure);
    std::shared_ptr<TrMassive<Figure>> *data;
    ~Massive();
    int len;
private:
    int Find_free_cell();
    
    
};



#endif
