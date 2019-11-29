#include "Square.h"
#include <iostream>
#include <cmath>

Square::Square() {
	Square(0);
}

Square::Square(size_t i) : side_a(i){
	std::cout << "Square created: " << side_a << std::endl;
}

Square::Square(std::istream &is) {
  	int a;
 	is >> a;
  	if(a >= 0) {
		side_a = a;
	}
	else {
  		std::cout << "Square not created!" << std::endl;
	}
}

Square::Square(const Square& orig) {
	std::cout << "Square copy created" << std::endl;
	side_a = orig.side_a;
}

double Square::Sq() {
	return (double)(side_a * side_a);
}

void Square::Print() {
	std::cout << "Square:" << *this;
}

Square::~Square() {
	std::cout << "Square deleted" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Square& obj){
	os << "Size of sides:" << obj.side_a << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Square& obj){
	int a;
	is >> a;
	if(a < 0){
		std::cout << "Wrong sizes! Not changed!" << std::endl;
	} else{
		obj.side_a=a;
		std::cout << "Square changed!" << std::endl;
	}
	return is;
}
