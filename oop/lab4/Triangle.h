#ifndef TRIANGLE_H
#define 	TRIANGLE_H
#include <cstdlib>
#include <iostream>
#include "Figure.h"
#include <stdbool.h>

class Triangle : public Figure{
public:
	Triangle();
	Triangle(std::istream &is);
	Triangle(size_t ai,size_t bi,size_t ci);
	Triangle(const Triangle& orig);

	Triangle& operator++();
	double Square() override;
	void Print() override;
	friend Triangle operator+(const Triangle& left,const Triangle& right);
	friend std::ostream& operator<<(std::ostream& os, const Triangle& obj);
	friend std::istream& operator>>(std::istream& is,  Triangle& obj);

	Triangle& operator=(const Triangle& right);
	bool operator==(const Triangle& right);

	virtual ~Triangle();
private:
	size_t a;
	size_t b;
	size_t c;
};

#endif
