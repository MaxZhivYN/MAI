#include "Triangle.h"
#include <iostream>
#include <cmath>
#include <stdbool.h>

int max(int a, int b);
int min(int a, int b);

int max(int a, int b){
		return a>b ? a:b;
}
int min(int a, int b){
	return a<b ? a:b;
}


Triangle::Triangle() : Triangle(0, 0, 0) {
}

Triangle::Triangle(size_t ai, size_t bi, size_t ci) {
	if(max(ai, max(bi, ci)) > min(bi, ci)+min(ai, max(bi, ci))){
		std::cout << "Wrong sides! Triangle not created!" << '\n';
	}	else if((ai>=0) && (bi>=0) && (ci>=0)){
			a=ai;
			b=bi;
			c=ci;
			std::cout << "Triangle created: " << a << ", " << b << ", " << c << std::endl;
	} else{
			std::cout << "Wrong sizes! Triangle not created!" << '\n';
		}
}


Triangle::Triangle(std::istream &is) {
	int ai, bi, ci;
	is >> ai;
	is >> bi;
	is >> ci;
	if(max(ai, max(bi, ci)) >= min(bi, ci)+min(ai, max(bi, ci))){
		std::cout << "Wrong sides! Triangle not created!" << '\n';
	}
	else if(ai>=0&&bi>=0&&ci>0){
		a=ai;
		b=bi;
		c=ci;
		std::cout << "Triangle created: " << a << ", " << b << ", " << c << std::endl;
	}
	else{
		std::cout << "Wrong sizes! Triangle not created!" << '\n';
	}
}


Triangle::Triangle(const Triangle& orig) {
	std::cout << "Triangle copy created" << std::endl;
	a = orig.a;
	b = orig.b;
	c = orig.c;
}

double Triangle::Square(){
 	double p = double(a + b + c) / 2.0;
	return sqrt(p * (p - double(a))*(p - double(b))*(p - double(c)));
}

Triangle& Triangle::operator=(const Triangle& right) {

	if (this == &right){
		return *this;
	}
	a = right.a;
	b = right.b;
	c = right.c;

	return *this;
}

Triangle& Triangle::operator++() {

	++a;
	++b;
	++c;

	return *this;
}

Triangle operator+(const Triangle& left,const Triangle& right) {

	return Triangle(left.a+right.a,left.b+right.b,left.c+right.c);
}

Triangle::~Triangle() {
	std::cout << "Triangle deleted" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Triangle& obj) {

	os << "a=" << obj.a << ", b=" << obj.b << ", c=" << obj.c << std::endl;
	return os;
}

void Triangle::Print(){
	std::cout << "Triangle: " << *this;
	return;
}

bool Triangle::operator==(const Triangle& right){
	return (a==right.a && b==right.b && c==right.c);
}

std::istream& operator>>(std::istream& is, Triangle& obj) {
	int ai, bi, ci;
	is >> ai;
	is >> bi;
	is >> ci;
	if(max(ai, max(bi, ci)) >= min(bi, ci)+min(ai, max(bi, ci))){
		std::cout << "Wrong sides! Triangle not changed!" << '\n';
	}
	else if(ai>=0&&bi>=0&&ci>0){
		obj.a=ai;
		obj.b=bi;
		obj.c=ci;
		std::cout << "Triangle changed! " << std::endl;
	}
	else{
		std::cout << "Wrong sizes! Triangle not changed!" << '\n';
	}

	return is;
}
