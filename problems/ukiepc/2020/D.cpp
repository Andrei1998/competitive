#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;
    long long int sum = 0;
    for (int i = 1; i <= N; ++i) {
        int v;
        cin >> v;
        sum += v;
    }
    if (sum % 3 == 0) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    return 0;
}