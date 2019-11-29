#ifndef SQUARE_H
#define SQUARE_H
#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Square : public Figure{
public:
	Square();
	Square(std::istream &is);
	Square(size_t i);
	Square(const Square& orig);

	int What_is_it() {return 2;}
	double Sq();
	void   Print();
	friend std::ostream& operator<<(std::ostream& os, const Square& obj);
	friend std::istream& operator>>(std::istream& is, Square& obj);

	virtual ~Square();
private:
	size_t side_a;
};

#endif
