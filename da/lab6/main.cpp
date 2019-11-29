#include <iostream>
#include <string>
#include "BigInteger.h"
using namespace std;

int main() {
	BigInteger bi;

	while (1) {
		cin >> bi;
		bi.Multiplication();
	}

	return 0;
}