#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int NMAX = 200000 + 5;
typedef long long int lint;
const lint INF = 1E18 + 15;

struct Node {
    int st, dr;
    lint minPlus;
    lint minMinus;
    lint minimum;
    lint lazy;

    void makeLazy(lint val) {
        minPlus += val;
        minMinus += val;
        minimum += val;
        if (st != dr)
            lazy += val;
    }
} tree[4 * NMAX];

void propagate(int node) {
    if (tree[node].lazy) {
        tree[node << 1].makeLazy(tree[node].lazy);
        tree[(node << 1) + 1].makeLazy(tree[node].lazy);
        tree[node].lazy = 0;
    }
}

void build(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;
    tree[node].minPlus = tree[node].minMinus = tree[node].minimum = INF;
    if (st == dr)
        return ;
    int mid = (st + dr) >> 1;
    build(node << 1, st, mid);
    build((node << 1) + 1, mid + 1, dr);
}

void update(int node, int where, lint val) {
    if (tree[node].st == tree[node].dr) {
        tree[node].minPlus = val + where;
        tree[node].minMinus = val - where;
        tree[node].minimum = val;
        return ;
    }
    propagate(node);

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (where <= mid)
        update(node << 1, where, val);
    else
        update((node << 1) + 1, where, val);

    tree[node].minPlus = min(tree[node << 1].minPlus, tree[(node << 1) + 1].minPlus);
    tree[node].minMinus = min(tree[node << 1].minMinus, tree[(node << 1) + 1].minMinus);
    tree[node].minimum = min(tree[node << 1].minimum, tree[(node << 1) + 1].minimum);
}

lint queryPlus(int node, int st, int dr) {
    if (tree[node].st == st && tree[node].dr == dr)
        return tree[node].minPlus;
    propagate(node);

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (dr <= mid)
        return queryPlus(node << 1, st, dr);
    else if (st > mid)
        return queryPlus((node << 1) + 1, st, dr);
    else
        return min(queryPlus(node << 1, st, mid),
                   queryPlus((node << 1) + 1, mid + 1, dr));
}

lint queryMinus(int node, int st, int dr) {
    if (tree[node].st == st && tree[node].dr == dr)
        return tree[node].minMinus;
    propagate(node);

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (dr <= mid)
        return queryMinus(node << 1, st, dr);
    else if (st > mid)
        return queryMinus((node << 1) + 1, st, dr);
    else
        return min(queryMinus(node << 1, st, mid),
                   queryMinus((node << 1) + 1, mid + 1, dr));
}

int main()
{
    //freopen("data.in", "r", stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int N, Q, A, B;
    cin >> N >> Q >> A >> B;

    build(1, 1, N);

    int last = B;
    update(1, A, 0);

    while (Q --) {
        int x;
        cin >> x;

        lint cost = min(x + queryMinus(1, 1, x),
                       -x + queryPlus(1, x, N));
        tree[1].makeLazy(abs(x - last));

        update(1, last, cost);
        last = x;
    }

    cout << tree[1].minimum << '\n';
    return 0;
}
