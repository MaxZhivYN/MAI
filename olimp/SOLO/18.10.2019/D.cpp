#include <iostream>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	int N;
	cin >> N;

	set<string> _set;

	string s;

	for (int i = 0; i < N; ++i) {
		cin >> s;
		sort(s.begin(), s.end());
		_set.insert(s);
	}

	cout << _set.size() << endl;

	return 0;
}