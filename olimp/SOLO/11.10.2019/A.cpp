#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
 
using namespace std;
 
typedef struct _team {
	string name;
	int tasksCount;
	int badPoints;
} team;
 
 
bool nameSortFunc(team& t1, team& t2) {
	return t1.name < t2.name;
}
 
bool tasksCountSortFunc(team& t1, team& t2) {
	return t1.tasksCount > t2.tasksCount;
}
 
bool badPointsSortFunc(team& t1, team& t2) {
	return t1.badPoints < t2.badPoints;
}
 
 
int main() {
	int N;
	cin >> N;
 
	vector<team> players(N);
 
	for (int i = 0; i < N; ++i) {
		cin >> players[i].name >> players[i].tasksCount >> players[i].badPoints;
	}
 
	sort(players.begin(), players.end(), tasksCountSortFunc);
	
	bool isSort = false;
	int beginID = 0;
 
	vector<team>::iterator begin = players.begin();
	vector<team>::iterator end = begin;
	for (int i = 0; i + 1 < N; ++i, ++end) {
		if (players[i].tasksCount == players[i + 1].tasksCount) {
			begin = end;
			++i;
 			++end;
			while (i + 1 < N && players[i].tasksCount == players[i + 1].tasksCount) {
				++i;
				++end;
			}
			++end;
			sort(begin, end, badPointsSortFunc);
			--end;
		}
	}
 
	//cout << endl;
	//for (int i = 0; i < N; ++i) {
	//	cout << players[i].name << " " << players[i].tasksCount << " " << players[i].badPoints << endl;;
	//}
 
	begin = players.begin();
	end = begin;
	for (int i = 0; i + 1 < N; ++i, ++end) {
		if (players[i].badPoints == players[i + 1].badPoints && players[i].tasksCount == players[i + 1].tasksCount) {
			begin = end;
			++i;
			++end;
			while (i + 1 < N && players[i].tasksCount == players[i + 1].tasksCount && players[i].badPoints == players[i + 1].badPoints) {
				++i;
				++end;
			}
			++end;
			sort(begin, end, nameSortFunc);
			--end;
		}
	}
 
 
 
 
	//cout << endl;
	for (int i = 0; i < N; ++i) {
		cout << players[i].name << endl;
	}
 
	return 0;
}