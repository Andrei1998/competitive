#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//18:14
const int NMAX = 100000 + 5;

int v[NMAX];
vector <int> allV;

vector <int> freq[NMAX];

struct Query {
    int ind;
    int k, l, pos;

    friend bool operator<(const Query &a, const Query &b) {
        return a.ind < b.ind;
    }
} queries[NMAX];

int anss[NMAX];

int aib[NMAX];

inline int lsb(int node) {
    return node & (-node);
}

void update(int where) {
    for (; where <= allV.size(); where += lsb(where))
        ++aib[where];
}

int kth(int k) {
    int who = 0;
    for (int i = 16; i >= 0; --i)
        if (who + (1 << i) <= allV.size() && aib[who + (1 << i)] < k) {
            who += (1 << i);
            k -= aib[who];
        }

    return who + 1;
}

int main()
{
    ios_base :: sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;

    for (int i = 1; i <= N; ++ i) {
        cin >> v[i];
        allV.push_back(v[i]);
    }

    sort(begin(allV), end(allV));
    allV.resize(unique(begin(allV), end(allV)) - allV.begin());

    for (int i = 1; i <= N; ++ i) {
        v[i] = lower_bound(allV.begin(), allV.end(), v[i]) - allV.begin() + 1;
        freq[v[i]].push_back(i - 1);
    }

    for (int i = 1; i <= Q; ++ i) {
        cin >> queries[i].k >> queries[i].ind >> queries[i].l;
        queries[i].pos = i;
        ++queries[i].ind;
    }

    sort(queries + 1, queries + Q + 1);

    int pos = 1;
    for (int i = 1; i <= Q; ++ i) {
        Query &it = queries[i];

        while (pos <= it.ind)
            update(v[pos ++]);

        int val = kth(it.k);
        if (it.l <= freq[val].size())
            anss[it.pos] = freq[val][it.l - 1];
        else
            anss[it.pos] = -1;
    }

    for (int i = 1; i <= Q; ++ i)
        cout << anss[i] << '\n';
    return 0;
}
