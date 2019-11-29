#include "Quadrate.h"
#include <iostream>
#include <cmath>

Quadrate::Quadrate() : Quadrate(0) {
}

Quadrate::Quadrate(size_t i) : side_a(i){
	std::cout << "Quadrate created: " << side_a << std::endl;
}

Quadrate::Quadrate(std::istream &is) {
  int a;
  is >> a;
  if(a>=0){
	side_a=a;
}
else{
  std::cout << "Quadrate not created!" << '\n';
}
}

Quadrate::Quadrate(const Quadrate& orig) {
	std::cout << "Quadrate copy created" << std::endl;
	side_a = orig.side_a;
}

double Quadrate::Square() {
	return (double)(side_a*side_a);
}

void Quadrate::Print() {
	std::cout << "Quadrate:" << *this;
}

Quadrate::~Quadrate() {
	std::cout << "Quadrate deleted" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Quadrate& obj){
	os << "Size of sides:" << obj.side_a << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Quadrate& obj){
	int a;
	is >> a;
	if(a < 0){
		std::cout << "Wrong sizes! Not changed!" << '\n';
	} else{
		obj.side_a=a;
		std::cout << "Quadrate changed!" << '\n';
	}
	return is;
}
