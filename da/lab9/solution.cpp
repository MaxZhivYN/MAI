#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;

set<int>* g;
vector<int> result;
char* used;
//int countL = 0;

void dfs(int v) {
	used[v] = true;
	result.push_back(v);
	for (auto i = g[v].begin(); i != g[v].end(); ++i) {
		if (!used[*i]) dfs(*i);
	}
}

int main() {
	int N, M;
	cin >> N >> M;

	used = new char[N + 1];
	//result.resize(N + 1);
	memset(used, 0, N + 1);
	g = new set<int>[N + 1];

	int v1, v2;
	for (int i = 0; i < M; ++i) {
		cin >> v1 >> v2;
		g[v1].insert(v2);
		g[v2].insert(v1);
	}

	for (int i = 1; i < N + 1; ++i) {
		if (!used[i]) {
			result.clear();
			//countL = 0;
			
			dfs(i);	
			sort(result.begin(), result.end());

			for (int j = 0; j < result.size(); ++j) {
				cout << result[j] << " ";
			}

			if (result.size() > 0) cout << endl;
		}
	}

	if (g) delete[] g;
	if (used) delete[] used;


	return 0;
}