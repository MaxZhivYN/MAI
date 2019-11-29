#include "BigInteger.h"


BigInteger::BigInteger() {
	this->BASE = pow(10, BigInteger::lengthBASE);
	this->first_inc = true;
	this->correct_data = true;
	this->countNumber = 0;
}

BigInteger::BigInteger(int n) {
 	this->BASE = pow(10, BigInteger::lengthBASE);
	this->first_inc = true;
	this->correct_data = true;
	this->countNumber = 0;

	this->digits.push_back(n);
	this->countNumber = this->countFirstDigit();
}

BigInteger::~BigInteger() {}

istream& operator>> (istream& in, BigInteger& bigint)
{

	if (!bigint.first_inc) {
		bigint.digits.clear();
	}

	string str;
	cin >> str;

	int countFirstDigit = 0;
	for (int i = str.length(); i > 0; i -= BigInteger::lengthBASE) {
		if (i < BigInteger::lengthBASE) {
			bigint.digits.push_back(atoi(str.substr(0, i).c_str()));
			countFirstDigit = str.substr(0, i).length();
		}
		else {
			bigint.digits.push_back(atoi(str.substr(i - BigInteger::lengthBASE, BigInteger::lengthBASE).c_str()));
		}
	}

	bigint.removeLeadingZeros();
	

	bigint.countNumber = (bigint.digits.size() - 1) * 9 + countFirstDigit;
	bigint.correct_data = true;
	bigint.first_inc = false;

	return in;
}


std::ostream& operator <<(std::ostream& os, const BigInteger& bigint)
{
	if (!bigint.correct_data) {
		os << "Error";
		return os;
	}

	if (bigint.digits.empty())
		os << 0;
	else {
		os << bigint.digits.back();
		os.fill('0');
		for (int i = static_cast<long long>(bigint.digits.size()) - 2; i >= 0; --i)
			os << setw(BigInteger::lengthBASE) << bigint.digits[i];
	}


	return os;
}


const BigInteger operator+(BigInteger left, const BigInteger& right)
{
	int bonus_disch = 0;
	size_t len = max(left.digits.size(), right.digits.size());

	for (size_t i = 0; i < len; i++) {
		if (i == left.digits.size())
			left.digits.push_back(0);

		if (i < right.digits.size()) {
			left.digits[i] += right.digits[i] + bonus_disch;

			if (left.digits[i] >= left.BASE) {
				left.digits[i] -= left.BASE;
				bonus_disch = 1;
			}
			else
				bonus_disch = 0;
		}
		else {
			left.digits[i] += bonus_disch;
			if (left.digits[i] >= left.BASE) // ������� ��� bonus_disch = 1 
				left.digits[i] -= left.BASE;
			else {
				bonus_disch = 0;
				break;
			}
		}
	}

	if (bonus_disch) {
		left.digits.push_back(bonus_disch);
	}

	left.correct_data = true;

	return left;
}


const BigInteger operator -(BigInteger left, const BigInteger& right)
{
	int bonusDisch = 0;
	for (int i = 0; i < right.digits.size() || bonusDisch; ++i) {
		left.digits[i] -= bonusDisch + (i < right.digits.size() ? right.digits[i] : 0);
		bonusDisch = left.digits[i] < 0;
		if (bonusDisch)  left.digits[i] += left.BASE;
	}

	left.removeLeadingZeros();

	left.correct_data = true;

	return left;
}


const BigInteger operator *(const BigInteger& left, const BigInteger& right)
{
	BigInteger result;
	result.digits.resize(left.digits.size() + right.digits.size());
	long long cur;
	long long carry = 0;
	for (size_t i = 0; i < left.digits.size(); ++i) {
		carry = 0;
		for (size_t j = 0; j < right.digits.size() || carry; ++j) {
			cur = result.digits[i + j] + static_cast<long long>(left.digits[i]) * 1LL * (j < right.digits.size() ? static_cast<long long>(right.digits[j]) : static_cast<long long>(0)) + carry;
			result.digits[i + j] = static_cast<int>(cur % left.BASE);
			carry = static_cast<int>(cur / left.BASE);
		}
	}

	result.removeLeadingZeros();

	return result;
}


const BigInteger operator *(const BigInteger& left, const int& right)
{
	BigInteger res;
	res.digits.resize(left.digits.size());

	long long cur, r = 0;
	for (long long i = 0; i < res.digits.size(); i++) {
		cur = static_cast<long long>(left.digits[i])* static_cast<long long>(right) + static_cast<long long>(r);
		r = cur / left.BASE;
		res.digits[i] = static_cast<int>(cur - r * left.BASE);
	}

	if (r != 0) res.digits.push_back(static_cast<int>(r));

	return res;
}


const BigInteger operator /(const BigInteger& left, const BigInteger& right)
{
	BigInteger result;
	if (right.digits.size() == 1 && right.digits[0] == 0) {
		result.correct_data = false;
		return result;
	}

	if (left.digits.size() == 1 && left.digits[0] == 0) {
		result.countNumber = 1;
		result.digits.push_back(0);
		result.correct_data = true;
		return result;
	}

	BigInteger b = right;
	BigInteger current;

	result.digits.resize(left.digits.size());
	int x, l, r;
	for (long long i = static_cast<long long>(left.digits.size()) - 1; i >= 0; --i) {
		current.digits.insert(current.digits.begin(), left.digits[i]);
		current.removeLeadingZeros();

		x = 0;
		l = 0;
		r = left.BASE;
		while (l <= r) {
			int m = (l + r) / 2;
			BigInteger t = b * m;
			if (t <= current) {
				x = m;
				l = m + 1;
			}
			else r = m - 1;
		}

		result.digits[i] = x;
		current = current - b * x;
	}

	result.removeLeadingZeros();
	result.correct_data = true;

	return result;
}

void BigInteger::removeLeadingZeros() {
	if (this->digits.size() == 1) return;

	for (int i = this->digits.size() - 1; i >= 0; i--) {
		if (this->digits.back() == 0)
			this->digits.pop_back();
		else break;
	}

}

bool operator <=(const BigInteger& left, const BigInteger& right) {
	if (right.digits.size() > left.digits.size() || 
		(right.digits.size() == left.digits.size() && right.countFirstDigit() > left.countFirstDigit())) return true;
	if (right.digits.size() < left.digits.size() ||
		(right.digits.size() == left.digits.size() && right.countFirstDigit() < left.countFirstDigit())) return false;

	for (int i = left.digits.size() - 1; i >= 0; --i) {
		if (left.digits[i] < right.digits[i]) {
			return true;
		}
		if (left.digits[i] > right.digits[i]) {
			return false;
		}
	}

	return true;
}

bool operator ==(const BigInteger& left, const BigInteger& right) {
	if (right.digits.size() != left.digits.size() ||
		(right.digits.size() == left.digits.size() && right.countFirstDigit() != left.countFirstDigit())) return false;


	for (int i = left.digits.size() - 1; i >= 0; --i) {
		if (left.digits[i] != right.digits[i]) {
			return false;
		}
	}

	return true;
}


bool operator <(const BigInteger& left, const BigInteger& right) {
	if (right.digits.size() > left.digits.size() ||
		(right.digits.size() == left.digits.size() && right.countFirstDigit() > left.countFirstDigit())) return true;
	if (right.digits.size() < left.digits.size() ||
		(right.digits.size() == left.digits.size() && right.countFirstDigit() < left.countFirstDigit())) return false;

	for (int i = left.digits.size() - 1; i >= 0; --i) {
		if (left.digits[i] < right.digits[i]) {
			return true;
		}
		if (left.digits[i] > right.digits[i]) {
			return false;
		}
	}

	return false;
}


bool operator >(const BigInteger& left, const BigInteger& right) {
	if (right.digits.size() < left.digits.size() ||
		(right.digits.size() == left.digits.size() && right.countFirstDigit() < left.countFirstDigit())) return true;
	if (right.digits.size() > left.digits.size() ||
		(right.digits.size() == left.digits.size() && right.countFirstDigit() > left.countFirstDigit())) return false;

	for (int i = left.digits.size() - 1; i >= 0; --i) {
		if (left.digits[i] > right.digits[i]) {
			return true;
		}
		if (left.digits[i] < right.digits[i]) {
			return false;
		}
	}

	return false;
}


const BigInteger operator ^(const BigInteger& a, const BigInteger& n) {
	BigInteger result;

	if (a.digits.size() == 1 && a.digits[0] == 0 && n.digits.size() == 1 && n.digits[0] == 0) {
		result.correct_data = false;
		return result;
	}

	result.digits.push_back(1);
	result.countNumber = 1;

	BigInteger aLocal = a;
	BigInteger nLocal = n;
	BigInteger zero(0);
	BigInteger two(2);

	while (!(nLocal == zero)) {
		if (!nLocal.BIntMOD2()) {
			result = result * aLocal;
		}

		aLocal = aLocal * aLocal;
		nLocal = nLocal / two;
	}


	result.correct_data = true;
	return result;
}

long long int bin_pow(long long a, long long n){
    long long res = 1;
    while(n){
        if(n % 2 != 0){
            res *= a;
        }
        a *= a;
        n /= 2;
    }
    return res;
}

bool BigInteger::BIntMOD2() {
	if (digits.size() > 0 && digits[0] % 2 == 0) return true;

	return false;
}
BigInteger& BigInteger::operator =(const BigInteger& right) {
	this->digits = right.digits;
	this->countNumber = right.countNumber;
	this->correct_data = right.correct_data;
	this->first_inc = right.first_inc;
	
	return *this;
}


int BigInteger::countFirstDigit() const {
	int count = 0;
	if (this->digits.size() > 0) {
		count = to_string(this->digits[this->digits.size() - 1]).length();
	}

	return count;
}
