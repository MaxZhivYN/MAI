#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<int, vector<int>> g;
vector<int> result;
vector<char> used;

bool dfs(int v) {
	used[v] = 1;

	for (int i = 0; i < g[v].size(); ++i) {
		switch (used[g[v][i]]) {
		case 0:
			if (!dfs(g[v][i])) return false;
			break;
		case 1:
			return false;
		}
	}
 
	used[v] = 2;

	result.push_back(v);
	return true;
}

int main() {
	int N, M;
	cin >> N >> M;

	used.resize(N + 1);
	fill(used.begin(), used.end(), 0);

	int v1, v2;
	for (int i = 0; i < M; ++i) {
		cin >> v1 >> v2;
		g[v1].push_back(v2);
	}
	
	for (int i = 1; i < N + 1; ++i) {
		if (used[i] == 0 && !dfs(i)) {
			cout << "-1" << endl;
			return 0;
		}
	}

	reverse(result.begin(), result.end());		

	for (int v : result) {
		cout << v << " ";
	}
	cout << endl;

	return 0;
}