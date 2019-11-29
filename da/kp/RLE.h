#pragma once

#include <string>

using namespace std;

class RLE {
public:
	void encriptRLE(string& str);
	void decriptRLE(string& str);

	string substrSymbol;
	string substrCount;

private:
	int converter(const char& symbol);
};

