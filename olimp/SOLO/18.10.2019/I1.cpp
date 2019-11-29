#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	int N;
	cin >> N;

	vector<int> vec(N);

	for (int i = 0; i < N; ++i) {
		cin >> vec[i];
	}

	int result = 0;

	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			for (int k = j + 1; k < N; ++k) {
				if ((vec[i] + vec[j]) > vec[k] && 
					(vec[i] + vec[k]) > vec[j] &&
					(vec[j] + vec[k]) > vec[i]) {
					++result;
				}
			}
		}
	}

	cout << result << endl;

	return 0;
}