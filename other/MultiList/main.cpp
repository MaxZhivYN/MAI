#include <iostream>
#include "conio.h"
#include "MultiList.h"
#include "Student.h"
using namespace std;

int CorrectIn(string s) {  //  Проверка корректности входного текста  //  s -- справка о данных, которые просят ввести
	string s1;
	bool correct_in = true;
	while (true) {
		cout << s;
		cin >> s1;
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
	return stoi(s1);
}


int main() {
	setlocale(LC_ALL, "russian");
	MultiList multilist;
	string s;
	int cmd = 0;

	while (true) {
		system("cls");
		
		cout << "Выберите, чтобы перейти:" << endl;
		cout << " 1 - Загрузка списка из файла " << endl;
		cout << " 2 - Добавление студента в список" << endl;
		cout << " 3 - Вывод всех студентов по алфавиту" << endl;
		cout << " 4 - Вывод всех студентов указанной группы по алфавиту" << endl;
		cout << " 5 - Вывод всех студентов указанной группы, отсортированных в порядке уменьшения суммы баллов." << endl;
		cout << " 6 - Вывод всех студентов, у которых сумма баллов ниже указанного значения." << endl;
		cout << " 7 - Сохранение списка в файл" << endl;
		cout << " 8 - Выход" << endl;
		cout << " 9 - Список" << endl;

		s = "Введите номер команды: ";

		cmd = CorrectIn(s); 
		cout << endl;

		switch (cmd) {
		case 1:
			system("cls");
			if (multilist.Load()) {
				cout << "Список упешно выгружен из файла." << endl;
			}
			else 
				cout << "Не удается выгрузить список из указанного вами файла." << endl;
			cout << "Нажмите любую кнопку" << endl;
			_getch();
			break;
		case 2:
			system("cls");
			if (multilist.Add_elem(cin, true)) {
				cout << "Студент успешно добавлен в список!" << endl;
			}
			else {
				cout << "Недостаточно памяти!" << endl;
				return 0;
			}
			cout << "Нажмите любую кнопку" << endl;
			_getch();
			break;
		case 3:
			system("cls");
			multilist.All_alph_print();
			cout << "Нажмите любую кнопку" << endl;
			_getch();
			break;
		case 4:
			system("cls");
			s = "Введите номер группы: ";
			
			cmd = CorrectIn(s);
			cout << endl;

			multilist.Group_alph_print(cmd);
			cout << "Нажмите любую кнопку" << endl;
			_getch();
			break;
		case 5:
			system("cls");
			s = "Введите номер группы: ";
			cmd = CorrectIn(s);
			cout << endl;

			multilist.Group_points_print(cmd);
			cout << "Нажмите любую кнопку" << endl;
			_getch();
			break;

		case 6:
			system("cls");
			s = "Введите сумму балов: ";
			cmd = CorrectIn(s);
			cout << endl;
			
			multilist.All_points_print(cmd);
			cout << "Нажмите любую кнопку" << endl;
			_getch();
			break;
		case 7:
			system("cls");
			if (multilist.Save()) {
				cout << "Список упешно сохранен в файл." << endl;
			}
			else
				cout << "Не удается сохранить список в указанный вами файл." << endl;
			cout << "Нажмите любую кнопку" << endl;
			_getch();
			break;
		case 8:
			cout << "////by\\\\" << endl;
			return 0;
		case 9:
			system("cls");
			multilist.Print();
			cout << "Нажмите любую кнопку" << endl;
			_getch();
			break;
		default:
			cout << "Команда не верна." << endl;
			cout << "Нажмите любую кнопку" << endl;
			_getch();
			break;
		}
	}
}