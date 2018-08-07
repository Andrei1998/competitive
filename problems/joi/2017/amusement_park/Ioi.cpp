#include "Ioi.h"
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 10000 + 5;
int N;
int father[NMAX];
int h[NMAX];

int find(int node) {
    if (father[node] != father[father[node]])
        father[node] = find(father[node]);
    return father[node];
}

bool unite(int a, int b) {
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
void getInitSet(int node, int father) {
    if (Set.size() + 1 <= 60) {
        Set.insert(node);
        type[node] = Set.size() - 1;
    }
    for (auto it: graph[node])
        if (it != father)
            getInitSet(it, node);
}

static int myNode;
static set <int> S;
bool done;
void evolve(int node, int father) {
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

        if (Set.count(myNode)) {
            S = Set;
            done = true;
            return ;
        }

        for (auto it: graph[node])
            if (it != father && !done)
                evolve(it, node);

        Set.erase(node);
        Set.insert(deleted);
    }
    else {
        if (Set.count(myNode)) {
            S = Set;
            done = true;
            return ;
        }

        for (auto it: graph[node])
            if (it != father && !done)
                evolve(it, node);
    }
}

static long long int X = 0;

void lastDfs(int node, int father) {
    for (auto it: graph[node])
        if (S.count(it) && it != father) {
            bool bit = Move(it - 1);
            if (bit)
                X |= (1LL << type[it]);
            lastDfs(it, node);
            Move(node - 1);
        }
}

long long int Ioi(int _N, int _M, int _A[], int _B[], int _P, int _V, int _T) {
    N = _N;
    myNode = _P + 1;
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

    if (_V)
        X |= (1LL << type[myNode]);
    lastDfs(myNode, 0);
    return X;
}
