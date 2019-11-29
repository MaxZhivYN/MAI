#include <cstdio>
#include <iostream>
#include "BTree.h"
#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

char LowerCase(char ch)
{
	return ch >= 'A' && ch <= 'Z' ? ch - 'A' + 'a' : ch;
}

bool IsLetter(char ch)
{
	return ch >= 'a' && ch <= 'z';
}

void ReadLine(char *cmd, char *buff, unsigned long long *number, size_t &word_count) {
	char symb;
	size_t i = 0;
	symb = getchar();
	if (symb == EOF) {
		*cmd = 'Q';
		return;
	}

	if (symb == '+' || symb == '-') {
		getchar();
		*cmd = symb;

		while (true) {
			symb = LowerCase(getchar());
			if (!IsLetter(symb)) {
				break;
			}
			buff[i++] = symb;
		}

		word_count = i;
		buff[i] = '\0';
		if (*cmd == '+') {
			*number = 0;

			while ((symb = getchar()) != '\n') {
				*number = (*number) * 10 + symb - '0';
			}
		}
	}
	else if (symb == '!') {
		getchar();
		buff[0] = symb;

		while ((symb = getchar()) != ' ') {
			buff[i++] = symb;
		}

		buff[i] = '\0';
		i = 0;
		*cmd = buff[0];

		while ((symb = getchar()) != '\n') {
			buff[i++] = symb;
		}

		buff[i] = '\0';
	}
	else {
		*cmd = 'F';
		buff[0] = LowerCase(symb);
		i += 1;

		while ((symb = getchar()) != '\n') {
			buff[i++] = LowerCase(symb);
		}

		buff[i] = '\0';
	}
}



int main() {
	BTree tree;
	char cmd;
	//char buff[257];
	Type_fly key;
	//size_t word_count = 0;
	//unsigned long long number = -1;
	while (true) {
		ReadLine(&cmd, key.word, &key.number, key.word_count);

		if (cmd == 'Q') {
			break;
		}


		switch (cmd) {
		case '+': {
			/*
			Type *data = new Type;
			data->word = new char[257];
			Get_copy(buff, data->word);
			data->number = number;
			data->word_count = word_count;
			*/
			//cout << key.number << " " << key.word << " " << key.word_count << endl;
			if (tree.insert(key)) {
				printf("OK\n");
			}
			else {
				printf("Exist\n");
			}
			break;
		}
		case '-': {
			if (tree.new_remove(key.word)) {
				printf("OK\n");
			}
			else {
				printf("NoSuchWord\n");
			}
			break;
		}
		case 'L': {
			if (tree.Load(key.word)) {
				printf("OK\n");
			}
			break;
		}
		case 'S': {
			if (tree.Save(key.word)) {
				printf("OK\n");
			}
			break;
		}
		case 'F': {
			Type *data = tree.search(key.word);
			if (data == nullptr) {
				printf("NoSuchWord\n");
			}
			else {
				printf("OK: %llu\n", data->number);
			}
			break;
		}
		}

		//tree.Print();
		/*
		if (!tree.Is_BTree()) {
			cout << "It is not a BTree" << endl;

			break;
		}
		else {
			cout << "Sucsess: it is Btree" << endl;
			char *ll = nullptr;
			tree.Print(ll);
		}*/

	}
	return 0;
}
