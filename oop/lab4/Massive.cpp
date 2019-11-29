#include "Massive.h"
#include <iostream>
#include <cstdlib>
#include <memory>

template <class T> TrMassive<T>::TrMassive() : TrMassive(0){}

template <class T> TrMassive<T>::TrMassive(unsigned int l) {
  data=nullptr;
  len=l;
  if(len>0){
    data = new std::shared_ptr<T>[len];
  }
  for (short int i=0; i<len; i++){
    data[i]=nullptr;
  }
  std::cout << "massive created!" << std::endl;
}

template <class T> TrMassive<T>::TrMassive(const TrMassive<T>& orig) {
  len=orig.len;
  data= new std::shared_ptr<T>[len];
  for(short int i=0; i<len; i++){
    data[i]=orig.data[i];
  }
  std::cout << "massive copied!" << '\n';
}

template <class T> bool TrMassive<T>::Empty(){
  return (len==0);
}

template <class T> std::shared_ptr<T>& TrMassive<T>::operator[](const int index){
  if(index<0){
    std::cout << "Wrong index! Returning element with index '0'!" << '\n';
    return data[0];
  } else if (index >= len){
    this->Resize(index+1);
  }
  return data[index];
}

template <class T> int TrMassive<T>::Lenght(){
  return len;
}

template <class T> TrMassive<T>::~TrMassive(){
  delete[] data;
  len=0;
  std::cout << "Massive deleted!" << '\n';
}

template <class T> void TrMassive<T>::Resize(int l){
  if(l<0){
    std::cout << "Wrong size!" << '\n';
    return;
  }
  std::shared_ptr<T>* data1;
  if(l==0){
    data1 = nullptr;
  } else{
    data1 = new std::shared_ptr<T>[l];
  }
  if (l<len){
    for (short int i = 0; i < l; i++) {
      data1[i]=data[i];
    }} else{
      short int i;
      for(i=0; i < len; i++){
        data1[i]=data[i];
      }
      while(i<l){
        data1[i]=nullptr;
        ++i;
      }}
  delete[] data;
  len=l;
  data=data1;
  data1=nullptr;
  return;
}

template <class A> std::ostream& operator<<(std::ostream& os, const TrMassive<A>& mass){
  std::cout << "Massive:" << '\n';
  std::cout << "Size:" << mass.len << '\n' << "Elements:" << std::endl;
  if(mass.len==0){
    std::cout << "Empty!" << '\n';
  }
  for(short int i=0; i<mass.len; i++){
    std::cout << "[" << i << "]" << ":";
    if(mass.data[i]!=nullptr){
      mass.data[i]->Print();
    }else{
      std::cout << "empty" << '\n';
    }
  }
  return os;
}

/* #include "Figure.h"
template class TrMassive<Figure>;
template std::ostream& operator<<(std::ostream& os, const TrMassive<Figure>& mass);
*/
