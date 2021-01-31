#include <bits/stdc++.h>

using namespace std;

const int NMAX = 10000;

int a[NMAX];
int b[NMAX];
int c[NMAX];

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> b[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < N; ++i) {
        vector<int> v = {a[i], b[i], c[i]};
        sort(v.begin(), v.end());
        cout << v[1] << " \n"[i + 1 == N];
    }
    return 0;
}