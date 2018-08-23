#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

const int NMAX = 2000 + 5;

int N;
int where[NMAX];

struct Point {
    int X, Y, W;

    friend bool operator<(const Point &a, const Point &b) {
        if (a.Y != b.Y)
            return a.Y < b.Y;
        else
            return a.X < b.X;
    }
} p[NMAX];

const long double EPS = 1E-20L;

struct Event {
    int angleP, angleQ;
    long double angle;
    int A, B;

    Event(int _angleP, int _angleQ, int _A, int _B):
        angleP(_angleP), angleQ(_angleQ), A(_A), B(_B) {
        angle = atan2l(angleQ, angleP);
    }

    static int compareAng(const Event &a, const Event &b) {
        //lint aux = 1LL * a.angleP * b.angleQ - 1LL * b.angleP * a.angleQ;
        //long double aux = atan2l(a.angleQ, a.angleP) - atan2l(b.angleQ, b.angleP);
        //long double aux = a.angle - b.angle;
        if (a.angle + EPS < b.angle)
            return -1;
        else if (a.angle - EPS > b.angle)
            return 1;
        else
            return 0;
    }

    friend bool operator<(const Event &a, const Event &b) {
        int cmp = compareAng(a, b);
        if (cmp != 0)
            return cmp == -1;
        else if (a.A != b.A)
            return a.A < b.A;
        else
            return a.B < b.B;
    }
};

vector <Event> events;

struct Node {
    int st, dr;
    lint sum;
    lint pref;
    lint suf;
    lint best;
} tree[4 * NMAX];

void unite(Node &res, const Node a, const Node &b) {
    res.sum = a.sum + b.sum;
    res.pref = max(a.pref, a.sum + b.pref);
    res.suf = max(b.suf, b.sum + a.suf);
    res.best = max(max(a.best, b.best), a.suf + b.pref);
}

int weights[NMAX];
void build(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;
    if (st == dr) {
        tree[node].sum = weights[st];
        tree[node].best = tree[node].suf = tree[node].pref = max(0, weights[st]);
    }
    else {
        int mid = (tree[node].st + tree[node].dr) >> 1;
        build(node << 1, st, mid);
        build((node << 1) + 1, mid + 1, dr);
        unite(tree[node], tree[node << 1], tree[(node << 1) + 1]);
    }
}

void update(int node, int where) {
    if (tree[node].st == tree[node].dr) {
        tree[node].sum = weights[where];
        tree[node].best = tree[node].suf = tree[node].pref = max(0, weights[where]);
        return ;
    }
    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (where <= mid)
        update(node << 1, where);
    else
        update((node << 1) + 1, where);
    unite(tree[node], tree[node << 1], tree[(node << 1) + 1]);
}

void doSwap(int where) {
    swap(weights[where], weights[where + 1]);
    update(1, where);
    update(1, where + 1);
}

lint doQuery() {
    return tree[1].best;
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> p[i].X >> p[i].Y >> p[i].W;
    sort(p + 1, p + N + 1);
    for (int i = 1; i <= N; ++ i)
        where[i] = i, weights[i] = p[i].W;
    build(1, 1, N);

    for (int i = 1; i <= N; ++ i)
        for (int j = i + 1; j <= N; ++ j)
            events.push_back(Event(p[j].X - p[i].X, p[j].Y - p[i].Y, i, j));
    sort(events.begin(), events.end());

    lint ans = doQuery();

    int j;
    for (int i = 0; i < events.size(); i = j + 1) {
        j = i;
        while (j + 1 < events.size() && Event :: compareAng(events[i], events[j + 1]) == 0)
            ++ j;
        for (int k = i; k <= j; ++ k) {
            doSwap(min(where[events[k].A], where[events[k].B]));
            swap(where[events[k].A], where[events[k].B]);
        }
        ans = max(ans, doQuery());
    }

    cout << ans << '\n';
    return 0;
}
