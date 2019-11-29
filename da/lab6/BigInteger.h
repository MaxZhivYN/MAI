#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class BigInteger
{
public:
	BigInteger() { first_inc = true; len_1 = 0; len_2 = 0; };
	~BigInteger() {};
	friend std::ostream& operator<< (ostream& out, const BigInteger& bigint);
	friend std::istream& operator>> (istream& in, BigInteger& bigint);
	//friend const BigInteger operator +(BigInteger left , const BigInteger& right);
	//friend const BigInteger operator -(BigInteger left, const BigInteger& right) {};
	//friend const BigInteger operator *(const BigInteger& left, const BigInteger& right) {};
	//friend const BigInteger operator /(const BigInteger& left, const BigInteger& right) {};
	//friend bool operator ==(const BigInteger& left, const BigInteger& right) {};
	//friend bool operator <(const BigInteger& left, const BigInteger& right) {};
	//friend bool operator >(const BigInteger& left, const BigInteger& right) {};
	void Sum();
	void Minus();
	void Multiplication();
	void Division();
	void Degree(int n) {};
	bool Less();  //  A < B
	bool More();  //  A > B
	bool Equal();  //  A == B
private:
	void Shift_right();
	static const int BASE = 1000000000;
	vector<int> digits_1;
	int len_1;
	vector<int> digits_2;
	int len_2;
	bool first_inc;
};



istream& operator>> (istream& in, BigInteger& bigint)
{
	if (!bigint.first_inc) {	
		bigint.digits_1.clear();
		bigint.digits_2.clear();
	}

	string str1, str2;
	cin >> str1 >> str2;
	bigint.len_1 = str1.length();
	bigint.len_2 = str2.length();

	if (str1.length() != 0) {
		for (long long i = str1.length(); i > 0; i -= 9) {
			if (i < 9)
				bigint.digits_1.push_back(atoi(str1.substr(0, i).c_str()));
			else
				bigint.digits_1.push_back(atoi(str1.substr(i - 9, 9).c_str()));
		}

		while (bigint.digits_1.size() > 1 && bigint.digits_1.back() == 0) {
			bigint.digits_1.pop_back();
		}
	}

	if (str2.length() != 0) {
		for (long long i = str2.length(); i > 0; i -= 9) {
			if (i < 9)
				bigint.digits_2.push_back(atoi(str2.substr(0, i).c_str()));
			else
				bigint.digits_2.push_back(atoi(str2.substr(i - 9, 9).c_str()));
		}

		while (bigint.digits_2.size() > 1 && bigint.digits_2.back() == 0) {
			bigint.digits_2.pop_back();
		}
	}

	bigint.first_inc = false;

	return in;
}


std::ostream& operator <<(std::ostream& os, const BigInteger& bi) {
	if (bi.digits_1.empty()) 
		os << 0;
	else {
		os << bi.digits_1.back();
		os.fill('0');
		for (long long i = static_cast<long long>(bi.digits_1.size()) - 2; i >= 0; --i) 
			os << setw(9) << bi.digits_1[i];
	}


	return os;
}


//const BigInteger operator +(BigInteger left, const BigInteger& right)
//{
//
//}


void BigInteger::Sum() 
{
	if (len_1 < len_2)
		swap(digits_1, digits_2);


	int bonus_disch = 0;
	for (size_t i = 0; i < digits_1.size(); i++) {
		if (i < digits_2.size()) {
			digits_1[i] += digits_2[i] + bonus_disch;
			
			if (digits_1[i] > BASE) {
				digits_1[i] -= BASE;
				bonus_disch = 1;
			}
			else 
				bonus_disch = 0;
		}
		else {
			digits_1[i] += bonus_disch;
			if (digits_1[i] > BASE) // заходит при bonus_disch = 1 
				digits_1[i] -= BASE;
			else break;
		}
	}

	if (bonus_disch) {
		digits_1.push_back(bonus_disch);
	}


	if (digits_1.empty()) 
		cout << 0;
	else {
		cout << digits_1.back();
		cout.fill('0');
		for (long long i = static_cast<long long>(digits_1.size()) - 2; i >= 0; --i)
			cout << setw(9) << digits_1[i];
	}
	cout << endl;
}


void BigInteger::Minus()
{
	if (len_1 < len_2) {
		cout << "ERROR" << endl;
		return;
	}
	int bonus_disch = 0;
	bool flag = true;
	for (size_t i = 0; i < digits_1.size(); ++i) {
		if (i < digits_2.size()) {

			if (flag) {
				if (digits_1[i] < digits_2[i]) {
					cout << "ERROR" << endl;
					return;
				}
				else if (digits_1[i] > digits_2[i])
					flag = false;
			}

			digits_1[i] -= (digits_2[i] + bonus_disch);
			if (digits_1[i] < 0) {
				digits_1[i] += BASE;
				bonus_disch = 1;
			}
		}
		else {
			digits_1[i] -= bonus_disch;
			if (digits_1[i] < 0) {
				digits_1[i] += BASE;
			}
			else 
				break;
		}
	}
	for (int i = digits_1.size() - 1; i >= 0; i--)
		if (digits_1.back() == 0)
			digits_1.pop_back();
		else break;


	if (digits_1.empty())
		cout << 0;
	else {
		cout << digits_1.back();
		cout.fill('0');
		for (long long i = static_cast<long long>(digits_1.size()) - 2; i >= 0; --i)
			cout << setw(9) << digits_1[i];
	}
	cout << endl;
}


bool BigInteger::More()  //   A > B
{
	if (len_1 > len_2)
		return true;
	else if (len_1 < len_2)
		return false;

	for (int i = digits_1.size(); i >= 0; i--) {
		if (digits_1[i] > digits_2[i])
			return true;
		else if (digits_1[i] < digits_2[i])
			return false;
	}

	return false;
}


bool BigInteger::Less()  //   A < B
{
	if (len_1 < len_2)
		return true;
	else if (len_1 > len_2)
		return false;

	for (int i = digits_1.size(); i >= 0; i--) {
		if (digits_1[i] < digits_2[i])
			return true;
		else if (digits_1[i] > digits_2[i])
			return false;
	}

	return false;
}


bool BigInteger::Equal()
{
	if (len_1 != len_2) return false;

	for (int i = digits_1.size(); i >= 0; i--) {
		if (digits_1[i] != digits_2[i])
			return false;
	}

	return true;
}


void BigInteger::Multiplication()
{
	vector<int> result;
	result.resize(digits_1.size() + digits_2.size());
	
	for (size_t i = 0; i < digits_1.size(); ++i) {
		short carry = 0;
		for (size_t j = 0; j < digits_2.size(); ++j) {
			long long cur = result[i + j] + digits_1[i] * 1LL * (j < digits_2.size() ? digits_2[j] : 0) + carry;
			result[i + j] = static_cast<int>(cur % BASE);
			carry = static_cast<int>(cur / BASE);
		}
	}

	for (size_t i = result.size() - 1; i >= 0 && result[i] == 0; --i)
		result.pop_back();

	if (result.empty())
		cout << 0;
	else {
		cout << result.back();
		cout.fill('0');
		for (long long i = static_cast<long long>(result.size()) - 2; i >= 0; --i)
			cout << setw(9) << result[i];
	}
	cout << endl;
}


//void BigInteger::Shift_right() {
//	if (this->_digits.size() == 0) {
//		this->_digits.push_back(0);
//		return;
//	}
//	this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
//	// здесь размер массива равен как минимум двум и перебор идет до предпоследнего разряда,
//	// поэтому i имеет "верный" тип size_t
//	for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
//	this->_digits[0] = 0;
//}



void BigInteger::Division()
{

}