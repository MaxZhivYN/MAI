#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>
using namespace std;

int n, m;

int largestArea(int *arr) {
	int* area = new int[m];
	memset(area, 0, m);
	stack<int> StL, StR;
	int t;

	for (int i = 0; i < m; i++) {
		while (!StL.empty() && arr[i] <= arr[StL.top()]) {
			StL.pop();
		}

		if (StL.empty())
			t = -1;
		else 
			t = StL.top();
		
		area[i] = i - t - 1;
		StL.push(i);
	}

	for (int i = m - 1; i >= 0; i--) {
		while (!StR.empty() && arr[i] <= arr[StR.top()]) {
			StR.pop();
		}

		if (StR.empty())
			t = m;
		else
			t = StR.top();
	
		area[i] += t - i - 1;
		StR.push(i);
	}

	int maxSq = 0;
	for (int i = 0; i < m; i++) {
		maxSq = max(maxSq, arr[i] * (area[i] + 1));
	}

	delete[] area;

	return maxSq;
}

int main() {
	cin >> n >> m;

	int** dp = new int*[n];
	char ch;
	int result = 0;
	for (int i = 0; i < n; ++i) {
		dp[i] = new int[m];
		for (int j = 0; j < m; ++j) {
			cin >> ch;
			if (ch == '1') dp[i][j] = 0;
			else dp[i][j] = 1;

			if (i > 0 && dp[i][j]) {
				dp[i][j] += dp[i - 1][j];
			}
		}

		result = max(result, largestArea(dp[i]));
	}

	for (int i = 0; i < n; ++i) {
		delete[] dp[i];
	}
	delete[] dp;

	cout << result << endl;

	return 0;
}