#include <iostream>
#include <vector>
#include <memory>
#include <cstring>
#include "Text.h"
#include "Sample.h"
using namespace std;



int main()
{
	Sample sample;
	long n = sample.Pattern_DB.Size();

	Text text(n);
	
	if (!text.Right_shift(n)) {
		return 0;
	}
	
	sample.Make_Pattern();
	sample.Make_R();
	sample.Make_N();

	sample.Make_L();
	for (int i = 0; i < n; ++i) {
		cout << sample.L[i] << " ";
	}
	cout << endl;
	sample.Make_l();
		for (int i = 0; i < n; ++i) {
		cout << sample.l[i] << " ";
	}
	cout << endl;

	long i;

	while (true) {
		i = n - 1;
		while (i >= 0) {
			if (text[i].M > 1 && sample.N[i] > 1) { // 1
				if (text[i].M < sample.N[i]) { // 2
					i -= text[i].M;
				}
				else if (text[i].M >= sample.N[i] && sample.N[i] == (i + 1)) // 3
					i = -1;
				else if (text[i].M > sample.N[i] && sample.N[i] < (i + 1)) { // 4
					i -= sample.N[i];
					break;
				}
				else if (text[i].M == sample.N[i] && sample.N[i] < (i + 1)) { // 5
					i -= text[i].M;
				}
			}
			else if (text[i].key != sample.Pattern_DB[i]) 
				break;
			else {
				i--;
			}
		}
		if (i < n - 2)
			text.Inc_M(n - 1, n - 1 - i);
		if (i < 0) { 
			cout << text[0].line << ", " << text[0].pos << endl;
			if (!text.Right_shift(n)) {
				delete[] sample.R;
				delete[] sample.N;
				delete[] sample.L;
				delete[] sample.l;
				return 0;
			}
		}
		else {
			if (!text.Right_shift(sample.Get_RSh_count(text[i].key, i))) {
				delete[] sample.R;
				delete[] sample.N;
				delete[] sample.L;
				delete[] sample.l;
				return 0;
			}
		}
		
	}
}