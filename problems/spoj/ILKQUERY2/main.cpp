#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 100000 + 5;

int N, Q;
int v[NMAX];

vector <int> allV;

vector <int> freq[NMAX];
int where[NMAX];
bool active[NMAX];

inline int lsb(int node) {
    return node & (-node);
}

int aib[NMAX];
int query(int where) {
    int ans = 0;
    for (; where; where -= lsb(where))
        ans += aib[where];
    return ans;
}

int query(int a, int b) {
    return query(b) - query(a);
}

void update(int where, int val) {
    for (; where <= N; where += lsb(where))
        aib[where] += val;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    //freopen("data.in", "r", stdin);

    cin >> N >> Q;
    for (int i = 1; i <= N; ++i) {
        cin >> v[i];
        allV.push_back(v[i]);
        active[i] = true;
        aib[i] = lsb(i);
    }

    sort(allV.begin(), allV.end());
    allV.resize(unique(allV.begin(), allV.end()) - allV.begin());

    for (int i = 1; i <= N; ++i) {
        v[i] = lower_bound(allV.begin(), allV.end(), v[i]) - allV.begin() + 1;
        freq[v[i]].push_back(i);
    }

    int sz = 0;
    for (int i = 1; i <= allV.size(); ++i)
        for (auto it: freq[i])
            where[it] = ++ sz;

    while (Q --) {
        bool type;
        cin >> type;

        if (!type) {
            int l, r, k;
            cin >> l >> r >> k;
            ++l, ++r;

            auto it = lower_bound(allV.begin(), allV.end(), k);

            if (it == allV.end())
                cout << "0\n";
            else if (*it != k)
                cout << "0\n";
            else {
                k = it - allV.begin() + 1;

                auto lptr = lower_bound(freq[k].begin(), freq[k].end(), l);
                int lpos = lptr - freq[k].begin();

                auto rptr = upper_bound(freq[k].begin(), freq[k].end(), r);
                int rpos = rptr - freq[k].begin();

                if (lpos >= rpos)
                    cout << "0\n";
                else {
                    rpos = where[freq[k][rpos - 1]];
                    if (lpos == 0)
                        lpos = where[freq[k][lpos]] - 1;
                    else
                        lpos = where[freq[k][lpos - 1]];

                    cout << query(lpos, rpos) << '\n';
                }
            }
        }
        else {
            int pos;
            cin >> pos;
            ++pos;

            update(where[pos], -active[pos]);
            active[pos] ^= 1;
            update(where[pos], active[pos]);
        }
    }
    return 0;
}
