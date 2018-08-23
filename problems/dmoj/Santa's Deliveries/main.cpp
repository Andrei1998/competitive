#include <bits/stdc++.h>

#define lint long long int
using namespace std;

const int NMAX = 1e5 + 5;

int N;
int delay[NMAX];

vector <int> tree[NMAX];
int father[NMAX];
lint dist[NMAX];

void dfs(int node) {
    for (auto it: tree[node]) {
        dist[it] += dist[node];
        dfs(it);
    }
}

int cnt[NMAX];

void add(int node, int val) {
    int nNode = node;
    while (dist[nNode] >= delay[node]) {
        cnt[nNode] += val;
        nNode = father[nNode];
    }
}

int dfsCompute(int node) {
    if (cnt[node])
        return 0;

    int maximum = 0;
    for (auto it: tree[node])
        maximum = max(maximum, dfsCompute(it));
    return maximum + 1;
}

#define lsb(x) ((x) & (-(x)))

int aib[NMAX];

void update(int where, int val) {
    for (; where <= N; where += lsb(where))
        aib[where] += val;
}

int query(int where) {
    int ans = 0;
    for (; where; where -= lsb(where))
        ans += aib[where];
    return ans;
}

int cauta() {
    int step = 1;
    while (2 * step <= N)
        step <<= 1;

    int ans = 0;
    for (; step; step >>= 1)
        if (ans + step <= N && aib[ans + step] == 0)
            ans += step;
    return ans;
}

int getWhere(int timeLimit) {
    int st = 1;
    int dr = N;
    int ans = 0;

    while (st <= dr) {
        int mid = (st + dr) >> 1;
        if (dist[mid] < timeLimit) {
            ans = mid;
            st = mid + 1;
        }
        else
            dr = mid - 1;
    }

    return ans;
}

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> delay[i];

    bool path = true;
    for (int i = 1; i <= N; ++ i) {
        cin >> father[i] >> dist[i];
        tree[father[i]].push_back(i);

        if (father[i] != i - 1)
            path = false;
    }

    dfs(0);

    if (path) {
        for (int i = 1; i <= N; ++ i) {
            int aux = getWhere(delay[i]);
            if (aux < i)
                update(aux + 1, 1);
        }

        int q = 0;
        cin >> q;

        while (q --) {
            int node;
            int val;
            cin >> node >> val;

            int aux = getWhere(delay[node]);
            if (aux < node)
                update(aux + 1, -1);

            delay[node] = val;

            aux = getWhere(delay[node]);
            if (aux < node)
                update(aux + 1, 1);

            cout << cauta() << '\n';
        }
        return 0;
    }

    for (int i = 1; i <= N; ++ i)
        add(i, 1);

    int q = 0;
    cin >> q;

    while (q --) {
        int node;
        int val;
        cin >> node >> val;

        add(node, -1);
        delay[node] = val;
        add(node, 1);

        cout << dfsCompute(0) - 1 << '\n';
    }

    return 0;
}
