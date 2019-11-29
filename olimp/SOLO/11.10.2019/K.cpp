#include <iostream>
#include <algorithm>
 
using namespace std;
 
int main() {
    int N, L;
    cin >> N >> L;
 
    char direction;
    int position, time = 0;
    for (int i = 0; i < N; ++i) {
        cin >> position >> direction;
        if (direction == 'R') {
            time = max(time, L - position);
        }
        else {
            time = max(time, position);
        }
    }
 
    cout << time;
 
    return 0;
}