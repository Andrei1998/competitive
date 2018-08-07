#include <bits/stdc++.h>

using namespace std;

int N, K;
set <pair <int, pair <int, int> > > edges;

void add(int a, int b, int c) {
    edges.insert(make_pair(a, make_pair(b, c)));
}
void del(int a, int b, int c) {
    edges.erase(make_pair(a, make_pair(b, c)));
}

void solve() {
    edges.clear();
    add(1, N, K);
    if (N == 2 || K <= 2) {
        cout << "0\n";
    }
    else {
        long long int cost = -K;
        add(1, 2, K - 1);
        add(2, N, K - 2);
        cost += (K - 1);
        cost += (K - 2);
        int edg = K - 3;
        int nd = 3;
        while (edg >= 1 && nd < N) {
            del(nd - 1, N, edg + 1);
            add(nd - 1, nd, edg + 1);
            add(nd, N, edg);
            cost += edg;
            nd ++;
            edg --;
        }
        cout << cost << '\n';
    }
    cout << edges.size() << endl;
    for (auto it: edges)
        cout << it.first << ' ' << it.second.first << ' ' << it.second.second << '\n';
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++ i) {
        cin >> N >> K;
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
