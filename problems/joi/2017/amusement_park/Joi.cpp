#include "Joi.h"
#include <bits/stdc++.h>

using namespace std;

static const int NMAX = 10000 + 5;

static int N;
static int father[NMAX];
static int h[NMAX];

static int find(int node) {
    if (father[node] != father[father[node]])
        father[node] = find(father[node]);
    return father[node];
}

static bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b)
        return false;

    if (h[a] < h[b])
        father[a] = b;
    else {
        if (h[a] == h[b])
            ++ h[a];
        father[b] = a;
    }
    return true;
}

static vector <int> graph[NMAX];
static set <pair <int, int> > edges;

static set <int> Set;
static int type[NMAX];
static void getInitSet(int node, int father) {
    if (Set.size() + 1 <= 60) {
        Set.insert(node);
        type[node] = Set.size() - 1;
    }
    for (auto it: graph[node])
        if (it != father)
            getInitSet(it, node);
}

static void evolve(int node, int father) {
    if (!Set.count(node)) {
        int deleted;
        for (auto leaf: Set)
            if (leaf != father) {
                int cnt = 0;
                for (auto it: Set)
                    if (it != leaf)
                        cnt += edges.count({leaf, it});
                if (cnt == 1) {
                    deleted = leaf;
                    break;
                }
            }

        Set.erase(deleted);
        Set.insert(node);
        type[node] = type[deleted];

        for (auto it: graph[node])
            if (it != father)
                evolve(it, node);

        Set.erase(node);
        Set.insert(deleted);
    }
    else {
        for (auto it: graph[node])
            if (it != father)
                evolve(it, node);
    }
}

void Joi(int _N, int _M, int _A[], int _B[], long long int _X, int _T) {
    N = _N;
    for (int i = 1; i <= N; ++ i)
        father[i] = i;
    for (int i = 0; i < _M; ++ i) {
        int a = _A[i] + 1;
        int b = _B[i] + 1;
        if (unite(a, b)) {
            graph[a].push_back(b);
            graph[b].push_back(a);
            edges.insert({a, b});
            edges.insert({b, a});
        }
    }

    getInitSet(1, 0);
    evolve(1, 0);

    for (int i = 1; i <= N; ++ i)
        if (_X & (1LL << type[i]))
            MessageBoard(i - 1, 1);
        else
            MessageBoard(i - 1, 0);
}
