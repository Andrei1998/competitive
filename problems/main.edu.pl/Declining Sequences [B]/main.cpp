#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

//11:07
#define lint long long int
using namespace std;

const int NMAX = 100000 + 5;
const int PMAX = 10 + 2;

int n, P, q;
int v[NMAX];

vector <int> allVals;

const lint INF = 1000000000000000000LL;
lint dp[PMAX][NMAX];

//Fenwick Tree
inline int lsb(int node) {
    return node & (-node);
}

lint aib[NMAX];

void init() {
    memset(aib, 0, (allVals.size() + 1) * sizeof(lint));
}

void update(int where, lint val) {
    for (; where <= allVals.size(); where += lsb(where)) {
        aib[where] += val;
        if (aib[where] > INF)
            aib[where] = INF;
    }
}

lint query(int where) {
    lint ans = 0;
    for (; where; where -= lsb(where)) {
        ans += aib[where];
        if (ans > INF)
            ans = INF;
    }
    return ans;
}

/*void solveBrute() {
    if (k > all) {
        cout << "-1\n";
        return ;
    }
    vector <int> sol;

    lint val = allVals.size();
    int start = 1;
    for (int p = P; p; -- p) {
        while (1) {
            if (v[start] > val) {
                ++ start;
                continue;
            }

            if (dp[p][start] < k)
                k -= dp[p][start ++];
            else {
                val = v[start] - 1;
                sol.push_back(start ++);
                break;
            }
        }
    }

    for (int i = 0; i < P; ++ i)
        cout << sol[i] << " \n"[i + 1 == P];
}*/

vector <int> positions[NMAX];

struct Node {
    int st, dr;
    lint sum;

    Node(int _st = 0, int _dr = 0, lint _sum = 0):
        st(_st), dr(_dr), sum(_sum) {}
} nodes[4 * NMAX];

void build(int node, int st, int dr) {
    nodes[node].st = st, nodes[node].dr = dr, nodes[node].sum = 0;
    if (st == dr)
        return ;

    int mid = (st + dr) >> 1;
    build(node << 1, st, mid);
    build((node << 1) + 1, mid + 1, dr);
}

void update(int node, int where, lint val) {
    nodes[node].sum += val;
    if (nodes[node].sum > INF)
        nodes[node].sum = INF;

    if (nodes[node].st == nodes[node].dr)
        return ;

    int mid = (nodes[node].st + nodes[node].dr) >> 1;
    if (where <= mid)
        update(node << 1, where, val);
    else
        update((node << 1) + 1, where, val);
}

int queryAint(int node, int start, lint &k) {
    int mid = (nodes[node].st + nodes[node].dr) >> 1;

    //Daca nu asta e startul
    if (nodes[node].st != start) {
        if (start > mid)
            return queryAint((node << 1) + 1, start, k);
        else {
            int ans = queryAint(node << 1, start, k);
            if (ans == mid + 1)
                return queryAint((node << 1) + 1, mid + 1, k);
            else
                return ans;
        }
    }

    if (nodes[node].sum < k) {
        k -= nodes[node].sum;
        return nodes[node].dr + 1;
    }

    if (nodes[node].st == nodes[node].dr)
        return nodes[node].st;

    int ans = queryAint(node << 1, start, k);
    if (ans == mid + 1)
        return queryAint((node << 1) + 1, mid + 1, k);
    else
        return ans;
}

vector <int> answers[NMAX];
vector <pair <int, pair <int, pair <int, lint> > > > queries;

int main()
{
    ios_base :: sync_with_stdio(false);
    //freopen("input.in", "r", stdin);

    cin >> n >> P >> q;
    for (int i = 1; i <= n; ++ i) {
        cin >> v[i];
        allVals.push_back(v[i]);
    }

    //Compress coordinates
    sort(allVals.begin(), allVals.end());
    allVals.resize(unique(allVals.begin(), allVals.end()) - allVals.begin());
    for (int i = 1; i <= n; ++ i)
        v[i] = lower_bound(allVals.begin(), allVals.end(), v[i]) - allVals.begin() + 1;

    for (int j = 1; j <= n; ++ j)
        dp[1][j] = 1;

    for (int i = 2; i <= P; ++ i) {
        init();

        for (int j = n; j; -- j) {
            dp[i][j] = query(v[j] - 1);
            if (dp[i][j] > INF)
                dp[i][j] = INF;
            update(v[j], dp[i - 1][j]);
        }
    }

    lint all = 0;
    for (int j = 1; j <= n; ++ j) {
        all += dp[P][j];
        if (all > INF)
            all = INF;
    }

    /*for (int i = 1; i <= P; ++ i) {
        cout << "i = " << i << endl;
        for (int j = 1; j <= n; ++ j)
            cout << dp[i][j] << ' ';
        cout << endl;
    }*/

    //Build persistent
    for (int i = 1; i <= n; ++ i)
        positions[v[i]].push_back(i);

    queries.reserve(q);
    for (int i = 1; i <= q; ++ i) {
        lint k;
        cin >> k;
        if (k <= all) {
            queries.push_back(make_pair(allVals.size() + 1, make_pair(1, make_pair(i, k))));
            answers[i].reserve(P);
        }
    }

    for (int p = P; p; -- p) {
        sort(queries.begin(), queries.end());
        build(1, 1, n);

        int val = 0;
        for (vector <pair <int, pair <int, pair <int, lint> > > > :: iterator it = queries.begin(); it != queries.end(); ++ it) {
            int &start = it -> second.first;
            int &lessThan = it -> first;
            int &who = it -> second.second.first;
            lint &k = it -> second.second.second;

            while (val + 1 < lessThan) {
                ++ val;
                for (vector <int> :: iterator it = positions[val].begin(); it != positions[val].end(); ++ it)
                    update(1, *it, dp[p][*it]);
            }

            start = queryAint(1, start, k);
            lessThan = v[start];
            answers[who].push_back(start);
        }
    }

    for (int i = 1; i <= q; ++ i)
        if (answers[i].empty())
            cout << "-1\n";
        else {
            for (int j = 0; j < P; ++ j)
                cout << answers[i][j] << " \n"[j + 1 == P];
        }
    return 0;
}
