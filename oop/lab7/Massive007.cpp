#include <iostream>
#include <cstdlib>
#include <memory>
#include "Massive007.h"


Massive::Massive() 
{
    len = 1;
    if (len > 0) {
        data = new std::shared_ptr<TrMassive<Figure>>[len];
    }
    for (int i = 0; i < len; ++i) {
        data[i] = std::make_shared<TrMassive<Figure>>(5);
    }
    std::cout << "massive007 created!" << std::endl;
}


std::shared_ptr<TrMassive<Figure>> Massive::operator[](int index)
{ 
    if (index > len) {
        Resize(len + 1);
    }
    return data[index];
}


Massive::~Massive()
{
    if (len > 0) {
        delete[] data;
    }
    std::cout << "Massive deleted!" << '\n';
}

int Massive::Lenght()
{
    return len;
}


void Massive::Resize(int l)
{
    if (l > len) {
		std::shared_ptr<TrMassive<Figure>> *temp = new std::shared_ptr<TrMassive<Figure>>[l];
		std::shared_ptr<TrMassive<Figure>> *pInt = data;
		std::copy(pInt, pInt + len, temp);
		std::swap(temp, data);
        len = l;
	}
    else {
        if (l > 0)
            std::cout << "The number you enter is smaller than the current array size. Enter a different size." << std::endl;
        else
            std::cout << "Enter correct number." << std::endl;
    }
}


std::ostream& operator<<(std::ostream& os, const Massive& mass) 
{
    std::cout << "Massive:" << std::endl;
    std::cout << "Size:" << mass.len << '\n' << "Elements:" << std::endl;
    if (mass.len == 0 ) {
        std::cout << "Empty!" << '\n';
    }
    for (short int i = 0; i < mass.len; i++) {
        std::cout << "[" << i << "]" << ": ";
        if (mass.data[i] != nullptr) {
            std::cout << *(mass.data[i]);
        } 
        else {
            std::cout << "empty" << std::endl;
        }
    }
    return os;
}

void Massive::Insert(std::shared_ptr<Figure> figure)
{
    for (int i = 0; i < len; ++i) {
        if (data[i]->Insert_to_cell(figure)) 
            return;
    }
    Resize(len + 1);
    data[len - 1] = std::make_shared<TrMassive<Figure>>(5);
    data[len - 1]->Insert_to_cell(figure);
}



int Massive::Find_free_cell()
{
    return 0;
}


void Massive::Delete(int id)
{
    while (!(id >= 0 && id < len)) {
        std::cout << "Imput correct id" << std::endl;
        std::cin >> id;
    }
    int cmd;
    std::cout << "Enter:" << std::endl;
    std::cout << "1: Delete by figure's type" << std::endl;
    std::cout << "2: Delete by square" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> cmd;
    int id_cell = data[id]->number;

    switch (cmd) {
    case 1:
        std::cout << "Enter:" << std::endl;
        std::cout << "1: Triangle" << std::endl;
		std::cout << "2: Square" << std::endl;
		std::cout << "3: Rectangle" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> cmd;
        switch (cmd) {
        case 1:
            for (int i = 0; i < id_cell; i++) {
                if (data[id]->data[i].ptr->What_is_it() == 1) {
                    data[id]->data[i].ptr = nullptr;
                    data[id]->number--;
                }
            }
            break;
        case 2:
            for (int i = 0; i < id_cell; i++) {
                if (data[id]->data[i].ptr->What_is_it() == 2) {
                    data[id]->data[i].ptr = nullptr;
                    data[id]->number--;
                }
            }
            break;
        case 3:
            for (int i = 0; i < id_cell; i++) {
                if (data[id]->data[i].ptr->What_is_it() == 3) {
                    data[id]->data[i].ptr = nullptr;
                    data[id]->number--;
                }
            }
            break;
        default:
            std::cout << "Wrong choice!" << std::endl;
            break;
        }
        break;
    case 2:
        std::cout << "Enter square: ";
        std::cin >> cmd;
        while (cmd <= 0) {
            std::cout << "Imput correct square: ";
            std::cin >> cmd;
        }
        for (int i = 0; i < id_cell; i++) {
            if (data[id]->data[i].ptr->Sq() < cmd) {
                data[id]->data[i].ptr = nullptr;
                data[id]->number--;
            }
        }
        break;
    default:
        std::cout << "Wrong choice!" << std::endl;
        break;
    }
    if (data[id]->number <= 0) {
        std::cout << "YES" << std::endl;
        if (len - 1 == 0) return;
        std::cout << "NO" << std::endl;
        int i = 0, j = 0;
        for (int i = id; i < len; i++) {
            if (i + 1 < len) {
                std::swap(data[i], data[i + 1]);
            }
        }
        std::shared_ptr<TrMassive<Figure>> *temp = new std::shared_ptr<TrMassive<Figure>>[len - 1];
		std::shared_ptr<TrMassive<Figure>> *pInt = data;
		std::copy(pInt, pInt + len - 1, temp);
		std::swap(temp, data);
    } 
    else data[id]->QS();
}


/* #include "Figure.h"
template class Massive<Figure>;
template std::ostream& operator<<(std::ostream& os, const Massive<Figure>& mass);
*/
