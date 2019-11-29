#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include <istream>
using namespace std;

class Student 
{
public:
	Student() {
		FIO = "";
		Birth_Date = 0;
		group_number = 0;
		points = 0;
	};
	~Student() {};

	friend istream& operator>> (istream& in, Student& point)  // инициализация данных о студенте  //  используется при добавлении нового студента через меню 
	{
		bool correct_in = true;
		string s1;

		while (true) {
			cout << "Фамилия: ";
			in >> point.FIO;
			for (int i = 0; i < point.FIO.length(); ++i) {
				if (!isalpha(point.FIO[i])) {
					correct_in = false;
				}
			}

			if (!correct_in) {
				cout << "Введите коректные данные." << endl;
				correct_in = true;
			}
			else break;
		}


		while (true) {
			cout << "Имя: ";
			in >> s1;
			for (int i = 0; i < s1.length(); ++i) {
				if (!isalpha(s1[i])) {
					correct_in = false;
				}
			}
			if (!correct_in) {
				cout << "Введите коректные данные." << endl;
				correct_in = true;
			}
			else break;
		}
		
		point.FIO += " " + s1 + " ";

		while (true) {
			cout << "Отчество: ";
			in >> s1;
			for (int i = 0; i < s1.length(); ++i) {
				if (!isalpha(s1[i])) {
					correct_in = false;
				}
			}
			if (!correct_in) {
				cout << "Введите коректные данные." << endl;
				correct_in = true;
			}
			else break;
		}

		point.FIO += s1;

		while (true) {
			cout << "Год рождения: ";
			in >> s1;
			for (int i = 0; i < s1.length(); ++i) {
				if (!isdigit(s1[i])) {
					correct_in = false;
				}
			}
			if (!correct_in) {
				cout << "Введите коректные данные." << endl;
				correct_in = true;
			}
			else break;
		}
		point.Birth_Date = stoi(s1);


		while (true) {
			cout << "Номер группы: ";
			in >> s1;
			for (int i = 0; i < s1.length(); ++i) {
				if (!isdigit(s1[i])) {
					correct_in = false;
				}
			}
			if (!correct_in) {
				cout << "Введите коректные данные." << endl;
				correct_in = true;
			}
			else break;
		}
		point.group_number = stoi(s1);
		

		while (true) {
			cout << "Cумма баллов: ";
			in >> s1;
			for (int i = 0; i < s1.length(); ++i) {
				if (!isdigit(s1[i])) {
					correct_in = false;
				}
			}
			if (!correct_in) {
				cout << "Введите коректные данные." << endl;
				correct_in = true;
			}
			else break;
		}
		point.points = stoi(s1);
		
		
		return in;
	}
	void FileRead(istream& in) {  // инициализация данных о студенте  //  используется при загрузке студента через файл 
		string s1;
		in >> FIO;
		in >> s1;
		FIO += " " + s1 + " ";
		in >> s1;
		FIO += s1;

		in >> Birth_Date;

		in >> group_number;

		in >> points;
	};

	string FIO;   //  ФИО
	int Birth_Date;  //  Дата рождения
	int group_number;  //  Номер группы
	int points;  //  Сумма баллов
};

#endif //STUDENT_H