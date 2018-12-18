#include <bits/stdc++.h>

using namespace std;

int L;
inline int getTime(int d1, int d2) {
    if (d2 < d1)
        swap(d1, d2);
    if (d1 == 1)
        return (d2 - 1) / 2;
    else if (d1 % 2 == d2 % 2)
        return (d1 + d2) / 2 - 2;
    else
        return (d1 + d2) / 2 - 1;
}

inline int getDistUp(int l, int c) {
    return l;
}
inline int getDistDown(int l, int c) {
    return L - 1 - l;
}
inline int getDistLeft(int l, int c) {
    return c;
}
inline int getDistRight(int l, int c) {
    return L - 1 - c;
}

const int NMAX = 12000 + 5;
int N;
int X[NMAX], Y[NMAX];

inline int getDist(int node1, int node2) {
    if (node1 > node2)
        swap(node1, node2);
    if (node1 == N + 1) {
        return -1;
    }
    else if (node2 == N + 1) {
        return min(getDistDown(X[node1], Y[node1]), getDistLeft(X[node1], Y[node1]));
    }
    else if (node2 == N + 2) {
        return min(getDistUp(X[node1], Y[node1]), getDistRight(X[node1], Y[node1]));
    }
    else {
        return getTime(abs(X[node1] - X[node2]) + 1, abs(Y[node1] - Y[node2]) + 1);
    }
}

int ans[NMAX];
bool vis[NMAX];

int alzati(int _L, int _N, int _X[], int _Y[]) {
    N = _N, L = _L;
    for (int i = 0; i < N; ++i)
        X[i + 1] = _X[i], Y[i + 1] = _Y[i];

    const int S = N + 1;
    const int T = N + 2;

    for (int i = 1; i <= N + 2; ++i)
        ans[i] = 2 * L;

    ans[S] = 0;
    while (1) {
        int minimum = 2 * L, node = -1;
        for (int i = 1; i <= N + 2; ++i) {
            if (!vis[i]) {
                if (ans[i] < minimum) {
                    minimum = ans[i];
                    node = i;
                }
            }
        }

        vis[node] = true;
        if (node == T)
            break;

        for (int i = 1; i <= N + 2; ++i) if (!vis[i]) {
            int cst = getDist(node, i);
            if (cst != -1) {
                cst = max(cst, ans[node]);
                if (cst < ans[i])
                    ans[i] = cst;
            }
        }
    }

    return max(0, ans[T] - 1);
}

