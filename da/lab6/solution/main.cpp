#include <iostream>
#include <string>
#include "BigInteger.h"

bool isSpase(char symbol) {
	return symbol == '\n' || symbol == '\t' || symbol == ' ';
}


using namespace std;

char ch = ' ';

int main() {
	BigInteger a;
	BigInteger b;
	while (cin >> a >> b) {
		cin >> ch;
		switch (ch) {
		case '+':
			cout << (a + b) << endl;
			break;
		case '-':
			if (a < b) {
				cout << "Error" << endl;
			}
			else {
				cout << (a - b) << endl;
			}
			break;
		case '*':
			cout << (a * b) << endl;
			break;
		case '/':
			cout << (a / b) << endl;
			break;
		case '^':
			cout << (a ^ b) << endl;
			break;
		case '>':
			if (a > b) cout << "true" << endl;
			else cout << "false" << endl;
			break;
		case '<':
			if (a < b) cout << "true" << endl;
			else cout << "false" << endl;
			break;
		case '=':
			if (a == b) cout << "true" << endl;
			else cout << "false" << endl;
			break;
		}
	}

	return 0;
}

