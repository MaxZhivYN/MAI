#pragma once
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

class BWT {
public:
	void encriptBWT(string& str, int& count);
	void decriptBWT(string& str, int& count);
};