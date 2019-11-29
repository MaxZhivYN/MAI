#include <iostream>
#ifndef FIGURE_H
#define 	FIGURE_H

class Figure {
public:
	virtual double Sq() = 0;
	virtual void   Print() = 0;
	virtual int What_is_it() = 0;
	friend std::ostream& operator<<(std::ostream& os, Figure& obj);
	virtual ~Figure() {};
};

#endif
