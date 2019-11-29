#pragma once

#include <fstream>
#include <string>

using namespace std;

class MyFStream {
public:
	void writeStr(string& str, ofstream& out);
	void writeHStr(string& str, ofstream& out);
	void readStr(string& str, ifstream& in);
	void readHStr(string& str, ifstream& in);
};

