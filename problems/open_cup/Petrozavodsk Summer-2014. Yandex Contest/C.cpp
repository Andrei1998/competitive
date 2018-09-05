#include <bits/stdc++.h>

using namespace std;

vector <int> invert(const vector <int> &v) {
    vector <int> ans(v.size());
    for (int i = 0; i < v.size(); ++ i)
        ans[v[i]] = i;
    return ans;
}

const int NMAX = 100000 + 5;
typedef long long int lint;

int N;
int v[2 * NMAX];
int where[5];

lint sPart[2 * NMAX];
lint getSpart(int pos) {
    if (pos < 0)
        return 0;
    else
        return sPart[pos];
}

lint query(int r, int residue) {
    if (r < residue)
        return 0;
    else if (r >= N)
        r = N - 1;
    while (r % 5 != residue)
        -- r;
    return getSpart(r);
}

lint query(int l, int r, int residue) {
    return query(r, residue) - query(l - 1, residue);
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    N *= 5;
    for (int i = 0; i < N; ++ i) {
        cin >> v[i];
        v[N + i] = v[i];
    }

    for (int i = 0; i < 2 * N; ++ i)
        sPart[i] = getSpart(i - 5) + v[i];
    for (int i = 0; i < 5; ++ i)
        where[i] = i;

    int M = 0;
    cin >> M;
    while (M --) {
        char type;
        cin >> type;
        if (type == '?') {
            int x, y;
            cin >> x >> y; -- x, -- y;
            lint ans = 0;
            for (int i = 0; i < 5; ++ i) {
                int displace = where[i] - i;
                ans += query(x - displace, y - displace, i);
                ans += query(x + N - displace, y + N - displace, i);
            }
            cout << ans << '\n';
        }
        else if (type == '<') {
            int x;
            cin >> x;
            for (int i = 0; i < 5; ++ i) {
                int &val = where[i];
                val -= x;
                if (val < 0)
                    val += N;
            }
        }
        else if (type == '#') {
            vector <int> perm(5);
            for (int i = 0; i < 5; ++ i) {
                cin >> perm[i];
                --perm[i];
            }
            perm = invert(perm);
            for (int i = 0; i < 5; ++ i) {
                int &val = where[i];
                val = perm[val % 5] + (val / 5) * 5;
            }
        }
        else  // Should never occur
            assert(false);
    }
    return 0;
}
