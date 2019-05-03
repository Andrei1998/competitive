#include <bits/stdc++.h>

using namespace std;

void solve() {
    int N;
    cin >> N;
    string s;
    cin >> s;
    string out(s.size(), '-');
    for (int i = 0; i < s.size(); ++i) {
        out[i] = 'E' ^ 'S' ^ s[i];
    }
    cout << out;
}

int main() {
    int T = 0;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        solve();
        cout << '\n';
    }
}