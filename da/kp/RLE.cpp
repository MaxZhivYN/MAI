#include "RLE.h"

void RLE::encriptRLE(string& str) {
	string result = "";
	substrCount = "";
	substrSymbol = "";
	size_t i = 0, j = 1;
	
	while (i < str.length()) {
		while (j < str.length() && str[i] == str[j]) {
			++j;
		}
		result += (str[i] + to_string(j - i));
		result.push_back('#');

		substrSymbol += str[i];
		substrCount += (to_string(j - i) + " ");

		i += (j - i);
	}
	
	str = result;
}

void RLE::decriptRLE(string& str) {
	int i = 0;
	long long count = 0;
	char symbol;
	string result;

	while (i < str.length()) {
		symbol = str[i++];

		for (count = 0; str[i] != '#'; ++i) {
			count += count * 10 + converter(str[i]);
		}
		
		result.insert(result.end(), count, symbol);
		++i;
	}

	str = result;
}

int RLE::converter(const char& symbol) {
	switch (symbol) {
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
	}

	return -1;
}