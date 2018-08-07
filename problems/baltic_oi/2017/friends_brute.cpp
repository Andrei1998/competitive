#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cassert>
#include <set>
#include <utility>

using namespace std;

const int NMAX = 18;

int N, P, Q;
int graph[NMAX];

set <pair <int, int> > Set;

bool isGood[1 << NMAX];

bool good(int mask) {
    if (__builtin_popcount(mask) <= P) {
        int cnt = 0;
        for (int i = 0; i < N; ++ i)
            if (mask & (1 << i))
                for (int j = 0; j < N; ++ j)
                    if (!( mask & (1 << j)  ))
                        if (graph[i] & (1 << j))
                            ++ cnt;
        return cnt <= Q;
    }
    return false;
}

bool vis[1 << NMAX];
bool works[1 << NMAX];
int son[1 << NMAX];

void compute(int mask) {
    if (vis[mask])
        return ;
    vis[mask] = true;
    works[mask] = false;

    for (int submask = mask; submask; submask = ((submask - 1) & mask)) {
        if (isGood[submask]) {
            compute(mask - submask);
            if (works[mask - submask]) {
                works[mask] = true;
                son[mask] = submask;
                return ;
            }
        }
    }
}

int main() {
    //freopen("friends.in", "r", stdin);
    cin >> N >> P >> Q;

    for (int i = 0; i < N; ++ i) {
        int cnt = 0;
        cin >> cnt;
        while (cnt --) {
            int nd;
            cin >> nd;

            graph[i] |= (1 << nd);
            graph[nd] |= (1 << i);

            int a = min(i, nd);
            int b = max(i, nd);
            if (Set.count(make_pair(a, b)))
                Set.erase(make_pair(a, b));
            else
                Set.insert(make_pair(a, b));
        }
    }

    if (!Set.empty()) {
        cout << "detention\n";
        return 0;
    }

    for (int i = 0; i < (1 << N); ++ i)
        isGood[i] = good(i);

    vis[0] = true;
    works[0] = true;
    compute((1 << N) - 1);

    if (!works[(1 << N) - 1]) {
        cout << "detention\n";
        return 0;
    }

    cout << "home\n";

    vector <vector <int> > ans;
    int mask = ((1 << N) - 1);
    while (mask) {
        vector <int> aux;

        for (int i = 0; i < N; ++ i)
            if (son[mask] & (1 << i))
                aux.push_back(i);

        mask -= son[mask];
        ans.push_back(aux);
    }

    sort(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (auto it: ans) {
        assert(it.size() > 0);
        cout << it.size();
        for (auto it2: it)
            cout << ' ' << it2;
        cout << '\n';
    }
    return 0;
}
