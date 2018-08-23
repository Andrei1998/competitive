#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100000 + 5;

int N;
int v[NMAX];

int main() {
    ios_base :: sync_with_stdio(false);
    cin >> N;
    int freq[2] = {0};
    for (int i = 1; i <= N; ++ i) {
        cin >> v[i];
        ++ freq[v[i] % 2];
    }
    if (freq[0] >= freq[1])
        cout << "2 0\n";
    else
        cout << "2 1\n";
    return 0;
}
