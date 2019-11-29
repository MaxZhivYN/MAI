#ifndef MASSIVE_H
#define MASSIVE_H
#include <memory>

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
  ~TrMassive();

private:
  std::shared_ptr<T>* data;
  int len;
};

#include "Massive.cpp"

#endif
