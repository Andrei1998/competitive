#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>

using namespace std;

vector <int> allLabels;

const int NMAX = 100000 + 5;
const int QMAX = 100000 + 5;

struct Query {
    char type;
    int a, b;
    char sign;
} queries[QMAX];

int t[NMAX];
int l[NMAX];

const int NODESMAX = NMAX + QMAX * 3;

struct Node {
    int l, r;
    set <int> times;
} tree[4 * NODESMAX];

void build(int node, int l, int r) {
    tree[node].l = l, tree[node].r = r;
    if (l == r)
        return ;

    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build((node << 1) + 1, mid + 1, r);
}

map <int, int> label; // label[time]

void change(int node, int where, int t) {
    if (tree[node].times.count(t))
        tree[node].times.erase(t);
    else
        tree[node].times.insert(t);

    if (tree[node].l == tree[node].r)
        return ;

    int mid = (tree[node].l + tree[node].r) >> 1;
    if (where <= mid)
        change(node << 1, where, t);
    else
        change((node << 1) + 1, where, t);
}

int best, who;
void query(int node, int l, int r, int t) {
    if (tree[node].l == l && tree[node].r == r) {
        auto it = tree[node].times.lower_bound(t);
        if (it != tree[node].times.end()) {
            if (*it - t <= best) {
                best = *it - t;
                who = *it;
            }
        }

        if (it != tree[node].times.begin()) {
            -- it;
            if (t - *it < best) {
                best = t - *it;
                who = *it;
            }
        }
        return ;
    }

    int mid = (tree[node].l + tree[node].r) >> 1;
    if (r <= mid)
        query(node << 1, l, r, t);
    else if (l > mid)
        query((node << 1) + 1, l, r, t);
    else {
        query(node << 1, l, mid, t);
        query((node << 1) + 1, mid + 1, r, t);
    }
}

int main()
{
    freopen("data.in", "r", stdin);

    int N;
    cin >> N;

    for (int i = 1; i <= N; ++ i) {
        cin >> t[i] >> l[i];
        allLabels.push_back(l[i]);
    }

    int Q = 0;
    cin >> Q;

    for (int i = 1; i <= Q; ++ i) {
        cin >> queries[i].type;
        if (queries[i].type == 'T')
            cin >> queries[i].a >> queries[i].b;
        else if (queries[i].type == 'L') {
            cin >> queries[i].a >> queries[i].b;
            allLabels.push_back(queries[i].b);
        }
        else if (queries[i].type == 'F') {
            cin >> queries[i].sign >> queries[i].b;
            allLabels.push_back(queries[i].b - 1);
            allLabels.push_back(queries[i].b);
            allLabels.push_back(queries[i].b + 1);
        }
        else
            cin >> queries[i].b;
    }

    sort(allLabels.begin(), allLabels.end());
    allLabels.resize(unique(allLabels.begin(), allLabels.end()) - allLabels.begin());

    for (int i = 1; i <= N; ++ i)
        l[i] = lower_bound(allLabels.begin(), allLabels.end(), l[i]) - allLabels.begin() + 1;
    for (int i = 1; i <= Q; ++ i)
        if (queries[i].type == 'L')
            queries[i].b = lower_bound(allLabels.begin(), allLabels.end(), queries[i].b) - allLabels.begin() + 1;
        else if (queries[i].type == 'F')
            queries[i].b = lower_bound(allLabels.begin(), allLabels.end(), queries[i].b) - allLabels.begin() + 1;

    build(1, 1, allLabels.size());

    for (int i = 1; i <= N; ++ i) {
        label[t[i]] = l[i];
        change(1, l[i], t[i]);
    }

    int filterL = 1;
    int filterR = allLabels.size();

    for (int i = 1; i <= Q; ++ i)
        if (queries[i].type == 'F') {
            if (queries[i].sign == '<') {
                filterL = 1;
                filterR = queries[i].b - 1;
            }
            else if (queries[i].sign == '>') {
                filterL = queries[i].b + 1;
                filterR = allLabels.size();
            }
            else if (queries[i].sign == '.') {
                filterL = 1;
                filterR = allLabels.size();
            }
        }
        else if (queries[i].type == 'S') {
            best = 1E9;
            who = -1;

            query(1, filterL, filterR, queries[i].b);
            cout << who << '\n';
        }
        else if (queries[i].type == 'T') {
            change(1, label[queries[i].a], queries[i].a);
            label[queries[i].b] = label[queries[i].a];
            change(1, label[queries[i].a], queries[i].b);
        }
        else {
            change(1, label[queries[i].a], queries[i].a);
            change(1, queries[i].b, queries[i].a);
            label[queries[i].a] = queries[i].b;
        }

    return 0;
}
