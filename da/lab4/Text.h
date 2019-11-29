#ifndef TEXT_H
#define TEXT_H
#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;

struct TData {
	size_t key;
	size_t line;
	size_t pos;
	long M;
};

class Text {
public:
	bool Right_shift(size_t shift_count);
	TData operator[](size_t index);
	void Inc_M(size_t index, long M_value);
	void TPrint();
	Text(size_t Pattern_count);
	~Text();
private:
	TData* T;
	size_t Get_result_index(size_t i);
	size_t line;
	size_t pos;
	size_t local_index;
	size_t count;
};

#endif