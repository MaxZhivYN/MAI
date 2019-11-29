#include <memory>
#include <iostream>
#include <cstdlib>
#include "Massive.h"
#include "Massive007.h"
#include "Triangle.h"
#include "Figure.h"
#include "Rectangle.h"
#include "Square.h"
//Лабораторная работа №5
//Живых Максим Олегович М8О-207Б-17
//Класс контейнер: массив
//Классы фигур: треугольник, прямоугольник, квадрат
/* Необходимо  спроектировать и разработать Итератор для динамической структуры данных.

Итератор должен быть разработан в виде шаблона и должен уметь работать со всеми типами фигур.

Итератор должен позволять использовать структуру данных в операторах типа for. Например:
for(auto i : stack)  std::cout << *i << std::endl;

Нельзя использовать:
    • Стандартные контейнеры std.

Программа должна позволять:
    • Вводить произвольное количество фигур и добавлять их в контейнер.
    • Распечатывать содержимое контейнера.
    • Удалять фигуры из контейнера.
*/
void print_menu()
{
	std::cout << "\nMenu" << std::endl;
	std::cout << "1: Print massive" << std::endl;
	std::cout << "2: Enter figure" << std::endl;
	std::cout << "3: Resize " << std::endl;
	std::cout << "4: Make Itteration // Deleted" << std::endl; 
	std::cout << "5: Delete" << std::endl;
	std::cout << "0-Exit" << std::endl;
	std::cout << "Enter your choise: ";
}



int main()
{
 	short int i, j, cmd;
  	Massive mass;
 	std::shared_ptr<Figure> abc;

	while (true) {
		print_menu();
		std::cin >> cmd;
		std::cout << std::endl;
		switch (cmd) {
		case 1:
    		std::cout << mass << std::endl;
     		break;
		case 2:
			std::cout << "Enter:" << std::endl;
        	std::cout << "1: Triangle" << std::endl;
			std::cout << "2: Square" << std::endl;
			std::cout << "3: Rectangle" << std::endl;
        	std::cout << "Your choice: ";
        	std::cin >> cmd;
			switch (cmd) {
			case 1:
				std::cout << "Enter triangle: " << '\n';
          		abc = std::make_shared<Triangle>(std::cin);
          		mass.Insert(abc);
				break;
			case 2:
				std::cout << "Enter Square: " << '\n';
          		abc = std::make_shared<Square>(std::cin);
          		mass.Insert(abc);
				break;
			case 3:
				std::cout << "Enter rectangle: " << '\n';
          		abc = std::make_shared<Rectangle>(std::cin);
          		mass.Insert(abc);
			default:
				std::cout << "Wrong choice!" << std::endl;
			}
			break;
		case 3:
			std::cout << "Enter new size: ";
      		std::cin >> cmd;
      		mass.Resize(cmd);
      		std::cout << "New lenght: " << mass.Lenght() << std::endl;
      		break;
		case 4:
			//std::cout << mass.data[0] << std::endl;
			break;
		case 5:
			std::cout << "Imput mass id: ";
			std::cin >> cmd;
			std::cout << std::endl;
			mass.Delete(cmd);
			break;
		case 0:
			return 0;
      	}
	}
}
