#include "MyFStream.h"

void MyFStream::writeStr(string& str, ofstream& out) {
	int count = str.length();
	out.write((char*)&count, sizeof(count));

	for (int i = 0; i < count; ++i) {
		out.write(&str[i], 1);
	}
}

void MyFStream::writeHStr(string& str, ofstream& out) {
	string result;

	char buff = 0;
	int count = 0;
	for (int i = 0; i < str.length(); ++i) {
		buff = buff | ((str[i] - '0') << (7 - count));
		count++;
		if (count == 8) {
			result.push_back(buff);

			count = buff = 0;
		}
	}

	if (count != 0) result.push_back(buff);

	writeStr(result, out);

	int hLastCodeCount = str.length() % 8;
	if (hLastCodeCount == 0) hLastCodeCount = 8;
	out.write((char*)&hLastCodeCount, sizeof(hLastCodeCount));
}

void MyFStream::readStr(string& str, ifstream& in) {
	int count;
	in.read((char*)&count, sizeof(count));

	string result;
	result.resize(count);

	for (int i = 0; i < count; ++i) {
		in.read(&result[i], 1);
	}

	str = result;
}

void MyFStream::readHStr(string& str, ifstream& in) {
	string hstr, result;
	readStr(hstr, in);
	int hLastCodeCount;
	in.read((char*)&hLastCodeCount, sizeof(hLastCodeCount));

	char symbol;
	for (int i = 0; i < hstr.length() - 1; ++i) {
		for (int j = 0; j < 8; ++j) {
			symbol = hstr[i] & (1 << (7 - j));
			result.push_back(symbol ? '1' : '0');
		}
	}

	for (int j = 0; j < hLastCodeCount; ++j) {
		symbol = hstr[hstr.length() - 1] & (1 << (7 - j));
		result.push_back(symbol ? '1' : '0');
	}

	str = result;
}
