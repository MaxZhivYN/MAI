#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "vector.hpp"
using namespace std;
typedef unsigned long long ull;

typedef struct
{
	ull id;
	char mass_char[65];
}Type;




void Sort(MyVector<Type> &arr, ull SizeVector) {
	for (int i = 0; i < SizeVector; i += 1) {
		for (int j = 0; j < SizeVector - 1; j += 1) {
			if (arr[j].id > arr[j + 1].id) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}


int main(void)
{
	MyVector<Type> data(1);
	ull max_elem = 0;
	ull index = 0;
	short mass_char_count = 0;
	char ch;

	
	while (cin >> data[index].id) {  //  Ctrl + K, C  //  Ctrl + K, U
		
		getchar();
		
		while (true) {
			if ((ch = getchar()) != '\n' && ch != EOF) {
				data[index].mass_char[mass_char_count] = ch;
				++mass_char_count;
			}
			else {
				while (mass_char_count < 65) {
					data[index].mass_char[mass_char_count] = '\0';
					++mass_char_count;
				}
				break;
			}
		}
		
		++data.mass_number;
		max_elem = max(max_elem, data[index].id);
		++index;
		mass_char_count = 0;
		data.Is_ReSize();
	}


	ull size = data.Size();
	MyVector<Type> *pass = new MyVector<Type>[data.Size()];
	ull NumberInVector;
	for (int i = 0; i < size; ++i) {
		NumberInVector = (double)data[i].id  * ((double)size - 1) / (double)max_elem;
		pass[NumberInVector].Push_Back(data[i]);
	}

	for (int i = 0; i < size; ++i) {
		Sort(pass[i], pass[i].Size());
		for (int j = 0; j < pass[i].Size(); ++j) {
			cout << (pass[i][j].id) << "\t" << pass[i][j].mass_char << "\n";
		}
	}
	delete[] pass;
	return 0;
}