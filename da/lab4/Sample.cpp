#include "Sample.h"


Sample::~Sample() {}


Sample::Sample()
{
	ReadPattern();
}


bool Sample::ReadPattern() 
{
	size_t word;
	char c;

	if ((c = getchar()) == EOF)
		return false;
	ungetc(c, stdin);

	cin >> word;
	Pattern_DB.Push_Back(word);

 	while (true) {
		while (true) {
			c = getchar();
			if (c == EOF) return false;
			if (isspace(c)) {
				if (c == '\n') {
					return true;
				}
			}
			else {
				ungetc(c, stdin);
				break;
			}
		}

		cin >> word;
		Pattern_DB.Push_Back(word);
	}
}




void Sample::Make_Pattern() 
{
	size_t n = Pattern_DB.Size();
	Pattern = new size_t[n];
	bool *DB_readden = new bool[n];
	for (size_t i = 0; i < n; ++i) {
		DB_readden[i] = true;
	}

	size_t index = 0;
	bool first = true;
	size_t word_now;
	size_t id = 0;
	
	while (index < n) {
		for (size_t i = 0; i < n; ++i) {
			if (DB_readden[i]) {
				if (first) {
					word_now = Pattern_DB[i];
					Pattern_DB_home.Push_Back(word_now);
					first = false;
				}
				if (Pattern_DB[i] == word_now) {
					Pattern[i] = id;
					DB_readden[i] = false;
					++index;
				}
			}
		}
		++id;
		first = true;
	}

	delete[] DB_readden;
}





long Sample::DB_find_word(size_t word)
{
	for (size_t i = 0; i < Pattern_DB_home.Size(); ++i) {
		if (Pattern_DB_home[i] == word) {
			return i;
		}
	}

	return -1;
}


void Sample::Make_R()
{
	R = new MyVector<size_t>[Pattern_DB_home.Size()];
	MyVector<size_t>* R_now;
	for (long i = Pattern_DB.Size() - 1; i >= 0; --i) {
		R_now = R + Pattern[i];
		R_now->Push_Back(i);
	}
}


long Sample::Get_R(size_t word, size_t pi) {
	long ai = DB_find_word(word);

	if (ai == -1 || pi <= 0)
		return -1;
	for (long i = 0; i < R[ai].Size(); ++i)
		if (R[ai][i] < pi)
			return R[ai][i];
	return -1;
}


void Sample::Make_N()
{
	N = new size_t[Pattern_DB.Size()];

	long n = Pattern_DB.Size(), k, l, r, size;
	for (k = 0; k < n; k++) 
		N[k] = 0;

	
	for (k = n - 2, l = n - 1, r = n - 1; k >= 0; k--) {
		if (k <= l) {
			if (Pattern[k] == Pattern[n - 1]) { 
				r = k;
				l = k;
				while (l > 0 && Pattern[l - 1] == Pattern[n - 1 - (r - l + 1)])
					l--;
				N[k] = r - l + 1;
			}
		}
		else {
			size = N[n - 1 - (r - k)];
			if (size > 0) {
				if (k - size + 1 > l) 
					N[k] = size;
				else { 
					r = k;
					if (l > 0 && Pattern[l - 1] == Pattern[n - 1 - (r - l + 1)]) { 
						while (l > 0 && Pattern[l - 1] == Pattern[n - 2 - (r - l)])
							l--;
						N[k] = r - l + 1;
					}
					else 
						N[k] = k - l + 1;
				}
			}
		}
	}
}


void Sample::Make_L()
{
	L = new long[Pattern_DB.Size()];

	size_t n = Pattern_DB.Size();
	long i;

	for (i = 0; i < n; i++)
		L[i] = -1;
		
	for (long j = 0; j < n - 1; j++) {
		if (N[j] > 0) {
			i = n - N[j];
			L[i] = j;
		}
	}
}


void Sample::Make_l()
{
	l = new size_t[Pattern_DB.Size()];

	size_t n = Pattern_DB.Size();
	long j = 0;
	l[0] = j;

	for (long i = n - 1; i > 0; i--) {
		if (N[n - 1 - i] == n - i)
			j = n - i;
		l[i] = j;
	}
}


size_t Sample::Get_RSh_count(size_t word, size_t i)
{
	size_t bmCharShift = i - Get_R(word, i);
	size_t bmSuffixShift;

	if (i < Pattern_DB.Size() - 1) {
		if (L[i + 1] >= 0)
			bmSuffixShift = Pattern_DB.Size() - 1 - L[i + 1];
		else
			bmSuffixShift = Pattern_DB.Size() - l[i + 1];
		return (bmCharShift > bmSuffixShift ? bmCharShift : bmSuffixShift);
	}
	else
		return bmCharShift;
}

