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
	unsigned long long result = 0;
	int end = N - 1, endGlobal = N - 1, endLocal;

	for (int k = N - 1; 0 <= k; --k) {
		end = k;
		for (int i = 0; i <= endGlobal && i < end; ++i) {
			for (int j = i + 1; j < end; ++j) {
				if ((vec[i] + vec[j]) > vec[k]) {
					end = j;
					break;
				}
			}
			if (end != k) {
				result += (k - end);
			}
		}

		endLocal = min(endGlobal, end);
		if (k - endLocal - 1 > 0) {
			result += ((k - endLocal) * (k - endLocal - 1) / 2);
		}



		endGlobal = end;
	}

	cout << result << endl;

	return 0;
}