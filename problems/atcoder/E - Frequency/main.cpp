#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 100000 + 5;

int N;
int v[NMAX];

typedef long long int lint;
lint anss[NMAX];

vector <pair <int, lint> > sol;
vector <int> allV;

int normal(int nr) {
    return lower_bound(allV.begin(), allV.end(), nr) - allV.begin() + 1;
}


lint aib[NMAX];
lint aibSum[NMAX];

inline int lsb(int node) {
    return node & (-node);
}

void update(lint aib[], int pos, lint val) {
    for (; pos <= allV.size(); pos += lsb(pos))
        aib[pos] += val;
}

lint query(lint aib[], int pos) {
    lint ans = 0;
    for (; pos; pos -= lsb(pos))
        ans += aib[pos];
    return ans;
}

lint queryUp(lint aib[], int pos) {
    lint ans = query(aib, allV.size());
    if (pos > 0)
        ans -= query(aib, pos - 1);
    return ans;
}

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> v[i];
        allV.push_back(v[i]);
    }

    sort(allV.begin(), allV.end());
    allV.resize(unique(begin(allV), end(allV)) - begin(allV));

    for (int i = 1; i <= N; ++ i) {
        update(aib, normal(v[i]), 1);
        update(aibSum, normal(v[i]), v[i]);
    }

    int maximum = 0;
    for (int i = 1; i <= N; ++ i) {
        if (v[i] > maximum) {
            sol.push_back(make_pair(i, queryUp(aibSum, normal(maximum)) - 1LL * maximum * queryUp(aib, normal(maximum))));
            maximum = v[i];
        }

        update(aib, normal(v[i]), -1);
        update(aibSum, normal(v[i]), -v[i]);
    }

    reverse(sol.begin(), sol.end());

    anss[sol[0].first] = sol[0].second;
    for (int i = 1; i < sol.size(); ++ i)
        anss[sol[i].first] = sol[i].second - sol[i - 1].second;

    for (int i = 1; i <= N; ++ i)
        cout << anss[i] << '\n';
    return 0;
}
