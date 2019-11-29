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
 
    sort(vec.begin(), vec.end());
 
    int result;
    if (N == 0)
        result = 0;
    else
        result = 1;
 
    for (int i = 1; i < N; ++i) {
        if (vec[i] != vec[i - 1]) {
            ++result;
        }
    }
 
    cout << result;
    return 0;
}