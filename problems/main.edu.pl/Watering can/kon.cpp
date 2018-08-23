#include <iostream>

using namespace std;

const int NMAX = 300000 + 5;

struct Node {
    int st, dr;
    int maximum;
    int maxPos;

    int lazy;
    void makeLazy(int val) {
        lazy += val;
        maximum += val;
    }
} tree[4 * NMAX];

void propagate(int node) {
    if (tree[node].lazy) {
        tree[node << 1].makeLazy(tree[node].lazy);
        tree[(node << 1) + 1].makeLazy(tree[node].lazy);
        tree[node].lazy = 0;
    }
}

int N, K;
int *init;

void build(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;
    if (st == dr) {
        tree[node].maximum = init[st - 1];
        tree[node].maxPos = st;
        return ;
    }

    int mid = (tree[node].st + tree[node].dr) >> 1;
    build(node << 1, st, mid);
    build((node << 1) + 1, mid + 1, dr);

    if (tree[node << 1].maximum > tree[(node << 1) + 1].maximum) {
        tree[node].maximum = tree[node << 1].maximum;
        tree[node].maxPos = tree[node << 1].maxPos;
    }
    else {
        tree[node].maximum = tree[(node << 1) + 1].maximum;
        tree[node].maxPos = tree[(node << 1) + 1].maxPos;
    }
}

void update(int node, int st, int dr) {
    if (tree[node].st == st && tree[node].dr == dr) {
        tree[node].makeLazy(1);
        return ;
    }
    propagate(node);

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (dr <= mid)
        update(node << 1, st, dr);
    else if (st > mid)
        update((node << 1) + 1, st, dr);
    else {
        update(node << 1, st, mid);
        update((node << 1) + 1, mid + 1, dr);
    }

    if (tree[node << 1].maximum > tree[(node << 1) + 1].maximum) {
        tree[node].maximum = tree[node << 1].maximum;
        tree[node].maxPos = tree[node << 1].maxPos;
    }
    else {
        tree[node].maximum = tree[(node << 1) + 1].maximum;
        tree[node].maxPos = tree[(node << 1) + 1].maxPos;
    }
}

void deny(int node, int where) {
    if (tree[node].st == tree[node].dr) {
        tree[node].maximum = -500000;
        return ;
    }

    propagate(node);

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (where <= mid)
        deny(node << 1, where);
    else
        deny((node << 1) + 1, where);

    if (tree[node << 1].maximum > tree[(node << 1) + 1].maximum) {
        tree[node].maximum = tree[node << 1].maximum;
        tree[node].maxPos = tree[node << 1].maxPos;
    }
    else {
        tree[node].maximum = tree[(node << 1) + 1].maximum;
        tree[node].maxPos = tree[(node << 1) + 1].maxPos;
    }
}

inline int lsb(int node) {
    return node & (-node);
}

int aib[NMAX];

void updateAib(int where) {
    for (; where <= N; where += lsb(where))
        ++ aib[where];
}

int queryAib(int where) {
    int ans = 0;
    for (; where; where -= lsb(where))
        ans += aib[where];
    return ans;
}

void inicjuj(int n, int k, int *D) {
    N = n, K = k, init = D;
    build(1, 1, N);

    while (tree[1].maximum >= K) {
        int where = tree[1].maxPos;
        deny(1, where);
        updateAib(where);
    }
}

void podlej(int l, int r) {
    update(1, l + 1, r + 1);

    while (tree[1].maximum >= K) {
        int where = tree[1].maxPos;
        deny(1, where);
        updateAib(where);
    }
}

int dojrzale(int l, int r) {
    return queryAib(r + 1) - queryAib(l);
}
