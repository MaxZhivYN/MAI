#pragma once

#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;


class BigInteger {
public:
	BigInteger();
	BigInteger(int n);
	~BigInteger();

	friend std::ostream& operator <<(ostream& out, const BigInteger& bigint);
	friend std::istream& operator >>(istream& in, BigInteger& bigint);

	friend const BigInteger operator +(BigInteger left, const BigInteger& right);
	friend const BigInteger operator -(BigInteger left, const BigInteger& right);
	friend const BigInteger operator *(const BigInteger& left, const BigInteger& right);
	friend const BigInteger operator *(const BigInteger& left, const int& right);
	friend const BigInteger operator /(const BigInteger& left, const BigInteger& right);
	friend const BigInteger operator ^(const BigInteger& a, const BigInteger& n);

	BigInteger& operator =(const BigInteger& right);
	

	friend bool operator <=(const BigInteger& left, const BigInteger& right);
	friend bool operator ==(const BigInteger& left, const BigInteger& right);
	friend bool operator <(const BigInteger& left, const BigInteger& right);
	friend bool operator >(const BigInteger& left, const BigInteger& right);

	int countFirstDigit() const;
private:
	bool BIntMOD2();
	void removeLeadingZeros();

	static const int lengthBASE = 4;
	int BASE;

	vector<int> digits;
	bool first_inc;
	bool correct_data;
	int countNumber;
};


