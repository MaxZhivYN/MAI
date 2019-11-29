#pragma once

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class MTF {
public:
	void encriptMTF(string& str, string& alph);
	void decriptMTF(string& str, string& alph);
private:
	int converter(const char& symbol);
};

