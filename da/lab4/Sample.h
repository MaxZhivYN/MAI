#ifndef SAMPLE_H
#define SAMPLE_H
#include <iostream>
#include <vector>
#include <cctype>
#include "MyVector.h"
using namespace std;


class Sample {
public:
	Sample();
	~Sample();

	
	size_t Get_RSh_count(size_t word, size_t i);

	MyVector<size_t> Pattern_DB;
	size_t* Pattern;
	MyVector<size_t>* R;
	void Make_Pattern();
	void Make_R();
	void Make_N();
	void Make_L();
	void Make_l();
	size_t* N;
	long* L;
	size_t* l;
	MyVector<size_t> Pattern_DB_home;

private:
	long DB_find_word(size_t word);
	long Get_R(size_t word, size_t pi);
	bool ReadPattern();

};
#endif