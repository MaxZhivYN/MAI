#ifndef MULTILIST_H
#define MULTILIST_H

#include <iostream>
#include <memory> 
#include <iomanip>
#include <fstream>
#include <ostream>
#include <istream>
#include "Student.h"
using namespace std;

class MultiList_Elem {  //  Элемент класс MultiList
public:
	MultiList_Elem() {  //  Конструктор для добавления студента через меню
		cin >> st;
	};
	MultiList_Elem(istream &file) {  //  Конструктор для добавления студента через файл
		st.FileRead(file);
	};
	~MultiList_Elem() {};

	class Way {  //  "Развилка" для элемента MultiList
	public:
		Way() {};
		~Way() {};
		shared_ptr<MultiList_Elem> prev;  //  Предыдущий элемент списка
		shared_ptr<MultiList_Elem> next;  //  Следующий элемент списка
	};

	Student st;
	
	Way stud_way;  //  "Развилка" для списка студентов
	Way alph_way;  //  "Развилка" для списка студентов отсортированных по алфавиту
	Way points_way;  //  "Развилка" для списка студентов отсортированных по сумме баллов
};


class MultiList
{
public:
	MultiList();
	~MultiList();
	bool Add_elem(istream& file, bool is_cin);  //  Добавление студента в мультисписок  //  file -- поток откуда будет выгружен студент  //  is_cin -- является ли этот поток cin
	void All_alph_print();  //  Вывод списка студентов отсортированного по алфавиту
	void Group_alph_print(int group);  //  Вывод списка студентов одной группы отсортированного по алфавиту  //  group -- группа
	void Group_points_print(int group);  //  Вывод списка студентов одной группы отсортированного по сумме баллов  //  group -- группа 
	void All_points_print(int points);  //  Вывод списка студентов отсортированного по сумме баллов и ниже опреденного  //  points -- верхняя граница суммы баллов
	void Print();  //  Вывод списка студентов
	bool Save();  //  Сохранение в файл
	bool Load();  //  Загрузка из файла
private:
	void DeleteList(shared_ptr<MultiList_Elem> listelem);  // удаление текущего списка из оперативной памяти
	class Ending {  //  "Крайние" элементы списка
	public:
		Ending() {};
		~Ending() {};
		shared_ptr<MultiList_Elem> first;
		shared_ptr<MultiList_Elem> last;
	};

	Ending stud_ending;  //  "Крайние"  для списка студентов
	Ending alph_ending;  //  "Крайние"  для списка студентов отстортированных по алфавиту
	Ending points_ending;  //  "Крайние"  для списка студентов отстортированных по сумме баллов
	size_t count;  //  Количество студентов
	};


#endif 

