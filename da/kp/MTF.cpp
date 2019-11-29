#include "MTF.h"

#include <set>

void MTF::encriptMTF(string& str, string& alph) {
	vector<int> valphFull(256, 0);
	for (int i = 0; i < str.length(); ++i) {
		++valphFull[str[i]];
	}
	string alphVec;
	for (int i = 0; i < valphFull.size(); ++i) {
		if (valphFull[i]) alphVec.push_back(i);
	}

	alph = alphVec;

	int index;
	string::iterator it;
	string result;
	char symbol;
	for (size_t i = 0; i < str.length(); ++i) {
		it = find(alphVec.begin(), alphVec.end(), str[i]);
		index = distance(alphVec.begin(), it);
		
		result.push_back(index);

		symbol = *it;
		alphVec.erase(it);
		alphVec.insert(alphVec.begin(), symbol);
	}

	str = result;
}

void MTF::decriptMTF(string& str, string& alph) {	
	string alphVec = alph;
	
	string::iterator it;
	string result = "";
	char symbol;	
	for (size_t i = 0; i < str.length(); ++i) {
		symbol = alphVec[str[i]];
		result.push_back(symbol);
		
		alphVec.erase(str[i], 1);
		alphVec.insert(0, 1, symbol);
	}

	// 5554110263772507410901310
	// aJHBHsBFHdAHssadkffkaj
	str = result;
}

int MTF::converter(const char& symbol) {
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
