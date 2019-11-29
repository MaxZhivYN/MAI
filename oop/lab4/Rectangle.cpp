#include "Rectangle.h"
#include <iostream>
#include <cmath>

Rectangle::Rectangle() : Rectangle(0, 0) {
}

Rectangle::Rectangle(size_t i, size_t j) : side_a(i), side_b(j) {
	std::cout << "Rectangle created: " << side_a << ", " << side_b << std::endl;
}

Rectangle::Rectangle(std::istream &is) {
  int a, b;
	is >> a;
	is >> b;
  if(a>=0&&b>=0){
    side_a=a;
    side_b=b;
  }
  else{
    std::cout << "Rectangle not created!" << '\n';
  }
}

Rectangle::Rectangle(const Rectangle& orig) {
	std::cout << "Rectangle copy created" << std::endl;
	side_a = orig.side_a;
	side_b = orig.side_b;
}

double Rectangle::Square() {
	return (double)(side_a*side_b);
}

void Rectangle::Print() {
	std::cout << "Rectangle:" << *this;
}

std::ostream& operator<<(std::ostream& os, const Rectangle& obj){
	os << "Size of sides: a=" << obj.side_a << ", b=" << obj.side_b << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Rectangle& obj){
	int a, b;
	is >> a;
	is >> b;
	if(a < 0 || b < 0){
		std::cout << "Wrong sizes! Not changed!" << '\n';
	} else{
		obj.side_a=a;
		obj.side_b=b;
		std::cout << "Quadrate changed!" << '\n';
	}
	return is;
}

Rectangle::~Rectangle() {
	std::cout << "Rectangle deleted" << std::endl;
}
