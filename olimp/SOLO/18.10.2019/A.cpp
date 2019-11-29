#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main() {
	int N;
	cin >> N;
 
	vector<size_t> vec(N);
 
	for (int i = 0; i < N; ++i) {
		cin >> vec[i];
	}
 
	sort(vec.begin(), vec.end());
 
	bool flag = true;
	for (int i = 0; i < N - 1; ++i) {
		if ((vec[i] + 1) != vec[i + 1]) {
			cout << "Scammed" << endl;
			flag = false;
			break;
		}
	}
 
	if (flag) {
		cout << "Deck looks good" << endl;
	}
 
	return 0;
}