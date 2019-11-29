#include <iostream>
#ifndef FIGURE_H
#define 	FIGURE_H

class Figure {
public:
	virtual double Square() = 0;
	virtual void   Print() = 0;
	friend std::ostream& operator<<(std::ostream& os, Figure& obj);
	virtual ~Figure() {};
};

#endif
