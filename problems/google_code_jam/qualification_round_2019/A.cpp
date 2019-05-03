#include <bits/stdc++.h>

using namespace std;

void solve() {
    string t;
    cin >> t;
    reverse(t.begin(), t.end());
    string a, b;
    for (auto ch: t) {
        if (ch == '4') {
            a += '2';
            b += '2';
        } else {
            a += ch;
            b += '0';
        }
    }
    while (a.size() > 1 && a.back() == '0') {
        a.pop_back();
    }
    while (b.size() > 1 && b.back() == '0') {
        b.pop_back();
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    cout << a << ' ' << b;
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