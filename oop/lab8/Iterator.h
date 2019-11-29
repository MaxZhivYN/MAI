#ifndef ITERATOR_H
#define ITERATOR_H
#include <memory>
#include <iostream>

template <class node, class T>
class Iterator
{
public:
    Iterator(node* n) 
    {
        node_ptr = n;
        index = 0;
        while (node_ptr[index].ptr == nullptr){
            ++index;
        }
        std::cout << "Iterator on elem with index:" << index << std::endl;
    }

    Iterator(node* n, int i)
    {
        node_ptr = n;
        index = i;
        while(node_ptr[index].ptr == nullptr) {
            ++index;
        }
        std::cout << "Iterator on elem with index:" << index << '\n';
    }

    std::shared_ptr<T> operator *()
    {
        return node_ptr[index].ptr;
    }

    std::shared_ptr<T> operator ->()
    {
        return node_ptr[index].ptr;
    }

    void operator ++() 
    {
        do{
            ++index;
        } while (node_ptr[index].ptr == nullptr);
    }

    Iterator operator ++(int)
    {
        Iterator iter(*this);
        ++(*this);
        return iter;
    }

    bool operator ==(Iterator const& i)
    {
        return (node_ptr == i.node_ptr && i.index == index);
    }

    bool operator !=(Iterator const& i)
    {
        return !(*this == i);
    }
private:
    node* node_ptr;
    int index;
};

#endif
