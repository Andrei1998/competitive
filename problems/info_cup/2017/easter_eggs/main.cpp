#include <bits/stdc++.h>

//10:49
using namespace std;

int query(vector <int> islands);

const int NMAX = 512 + 5;

vector <int> graph[NMAX];

int order[NMAX];
int sz;

int dfs(int node, int father) {
    order[++ sz] = node;
    for (auto it: graph[node])
        if (it != father)
            dfs(it, node);
}

int findEgg(int N, vector <pair <int, int> > bridges) {
    for (int i = 1; i <= N; ++ i)
        graph[i].clear();

    for (auto it: bridges) {
        int a = it.first;
        int b = it.second;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    sz = 0;
    dfs(1, 0);

    int st = 1;
    int dr = N;
    while (st < dr) {
        int mid = (st + dr) >> 1;

        vector <int> toQuery;
        for (int i = 1; i <= mid; ++ i)
            toQuery.push_back(order[i]);

        if (query(toQuery))
            dr = mid;
        else
            st = mid + 1;
    }
    return order[st];
}

#ifndef EVAL
int X, Q;
vector < int > g[512+10];

int main() {
    ifstream fin("input");

    int n, nr;
    vector < pair < int, int > > v;
    vector < int > Eggs;

    fin >> n >> nr; //there are nr Easter Eggs
    for (int i = 1; i <= nr; ++i) {
        int x; fin >> x; //the i-th Easter Eggs
        Eggs.push_back(x);
    }

    //the bridges
    for (int i = 1; i < n; ++i) {
        int x, y; fin >> x >> y;
        v.push_back({x, y});
        g[x].push_back(y);
        g[y].push_back(x);
    }

    for (vector < int > :: iterator it = Eggs.begin(); it != Eggs.end(); ++it) {
        Q = 0; X = *it;
        cout << findEgg(n, v) << '\n';
        cout << X << '\n';
        cout << '\n';
    }
}

bool used[512+10], is[512+10];

void browse(int node) {
    used[node] = 1;
    for (vector < int > :: iterator it = g[node].begin(); it != g[node].end(); ++it) {
        if (used[*it]) continue;
        if (is[*it]) browse(*it);
    }
}

bool beautiful(vector < int > v) {
    int n = (int)v.size();

    memset(used, 0, sizeof(used));
    memset(is, 0, sizeof(is));

    for (int i = 0; i < n; ++i)
        is[v[i]] = 1;

    browse(v[0]);
    for (int i = 0; i < n; ++i)
        if (!used[v[i]]) return 0;
    return 1;
}

int query(vector < int > v) {
    if (!beautiful(v)) {
        printf("The query-islands are not beautiful");
        exit(0);
    }

    bool res = 0; Q++;
    for (vector < int > :: iterator it = v.begin(); it != v.end(); ++it)
        res |= (X == *it);
    return res;
}
#endif // EVAL
