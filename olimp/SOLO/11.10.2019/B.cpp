#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main() {
	int N;
	cin >> N;
	vector<int> vec(N);
 
	for (int i = 0; i < N; ++i) {
		cin >> vec[i];
	}
	sort(vec.begin(), vec.end());
 
	for (int i = 0; i < N; ++i) {
		cout << vec[i] << " ";
	}
	return 0;
}