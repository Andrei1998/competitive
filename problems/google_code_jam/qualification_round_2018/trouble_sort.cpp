#include <bits/stdc++.h>

using namespace std;

string test() {
    int N;
    cin >> N;
    vector <int> v(N);
    for (int i = 0; i < N; ++ i)
        cin >> v[i];

    vector <int> parity[2];
    for (int i = 0; i < N; ++ i)
        parity[i & 1].push_back(v[i]);
    for (int i = 0; i < 2; ++ i)
        sort(parity[i].begin(), parity[i].end());

    for (int i = 0; i < (int)parity[0].size(); ++ i)
        v[2 * i]     = parity[0][i];
    for (int i = 0; i < (int)parity[1].size(); ++ i)
        v[2 * i + 1] = parity[1][i];

    int ans = -1;
    for (int i = 0; i + 1 < (int)v.size() && ans == -1; ++ i)
        if (v[i] > v[i + 1])
            ans = i;

    if (ans == -1)
        return "OK";
    else {
        stringstream ss;
        ss << ans;
        return ss.str();
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    int T = 0;
    cin >> T;
    for (int i = 1; i <= T; ++ i)
        cout << "Case #" << i << ": " << test() << '\n';
    return 0;
}
