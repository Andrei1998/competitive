#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3 * 100000 + 5;

int N;
struct Node {
    int st, dr;
    int ans;
    int valL, valR;

    int lenL1, lenL2;
    int lenR1, lenR2;
    int whereL;
    int whereR;
    int lazy;

    void makeLazy(int nr) {
        valL += nr;
        valR += nr;
        if (st < dr)
            lazy += nr;
    }
} tree[4 * NMAX];

void unite(Node &res, const Node a, const Node &b) {
    res.valL = a.valL;
    res.valR = b.valR;

    res.lenL1 = a.lenL1;
    if (a.lenL1 + 1 + a.lenL2 == a.dr - a.st + 1 && a.valR > b.valL) {
        if (b.lenL1 == 0)
            res.lenL2 = a.lenL2 + 1 + b.lenL2;
        else
            res.lenL2 = a.lenL2 + 1;
    }
    else
        res.lenL2 = a.lenL2;

    res.lenR2 = b.lenR2;
    if (b.lenR1 + 1 + b.lenR2 == b.dr - b.st + 1 && b.valL > a.valR) {
        if (a.lenR2 == 0)
            res.lenR1 = b.lenR1 + 1 + a.lenR1;
        else
            res.lenR1 = b.lenR1 + 1;
    }
    else
        res.lenR1 = b.lenR1;

    if (res.st == 1 && res.dr == 3)
        cout << "avem " << res.valL << ' ' << res.valR << ' ' << res.lenL2 << ' ' << res.lenR1 << endl;

    int ans = 1;
    if (a.whereR + a.lenR2 == a.dr && a.valR > b.valL) {
        if (b.lenL1 == 0)
            ans = max(ans, a.lenR2 + 1 + b.lenL2 + 1);
        else
            ans = max(ans, a.lenR2 + 1 + 1);
    }
    else
        ans = max(ans, a.lenR2);

    if (b.whereL - b.lenL1 == b.st && b.valL > a.valR) {
        if (a.lenL2 == 0)
            ans = max(ans, b.lenL1 + 1 + a.lenR1 + 1);
        else
            ans = max(ans, b.lenL1 + 1 + 1);
    }
    else
        ans = max(ans, b.lenL1);

    res.whereL = a.whereL;
    res.whereR = b.whereR;

    res.ans = max(max(a.ans, b.ans), max(res.lenL1 + 1 + res.lenL2, res.lenR1 + 1 + res.lenR2));
    res.ans = max(res.ans, ans);
}

void propagate(int node) {
    if (tree[node].lazy) {
        tree[node << 1].makeLazy(tree[node].lazy);
        tree[(node << 1) + 1].makeLazy(tree[node].lazy);
        tree[node].lazy = 0;
    }
}

int a[NMAX];
void build(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;

    if (st == dr)
        tree[node].valL = tree[node].valR = a[st], tree[node].ans = 1, tree[node].whereL = tree[node].whereR = st;
    else {
        int mid = (tree[node].st + tree[node].dr) >> 1;
        build(node << 1, st, mid);
        build((node << 1) + 1, mid + 1, dr);
        unite(tree[node], tree[node << 1], tree[(node << 1) + 1]);
    }
}

void update(int node, int st, int dr, int val) {
    if (tree[node].st == st && tree[node].dr == dr) {
        tree[node].makeLazy(val);
        return ;
    }
    propagate(node);

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (dr <= mid)
        update(node << 1, st, dr, val);
    else if (st > mid)
        update((node << 1) + 1, st, dr, val);
    else {
        update(node << 1, st, mid, val);
        update((node << 1) + 1, mid + 1, dr, val);
    }
    unite(tree[node], tree[node << 1], tree[(node << 1) + 1]);
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> a[i];
    build(1, 1, N);
    cout << tree[1].ans << endl;

    return 0;

    int M = 0;
    cin >> M;
    while (M --) {
        int l, r, d;
        cin >> l >> r >> d;
        update(1, l, r, d);
        cout << tree[1].ans << '\n';
    }
    return 0;
}
