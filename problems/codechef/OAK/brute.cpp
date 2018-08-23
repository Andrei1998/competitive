#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

const int NMAX = 100 + 5;

int N, M;
int w[NMAX];
int father[NMAX];
vector <int> graph[NMAX];

class Tree {
public:
    int acorns[NMAX];

    Tree() {
        memset(acorns, 0, sizeof acorns);
    }

    int add(int node, int val) {
        while (node) {
            acorns[node] += val;
            if (acorns[node] > w[node]) {
                scadUp(father[node], acorns[node] - val);
                reset(node);
                return node;
            }
            node = father[node];
        }
        return 0;
    }

    int reset(int node) {
        int ans = acorns[node];
        acorns[node] = 0;
        for (auto it: graph[node])
            reset(it);
        return ans;
    }

    void scadUp(int node, int val) {
        while (node) {
            acorns[node] -= val;
            node = father[node];
        }
    }
};

vector <Tree> states;

void test() {
    cin >> N >> M;
    for (int i = 0; i <= N; ++ i)
        graph[i].clear();

    for (int i = 1; i <= N; ++ i) {
        cin >> father[i] >> w[i];
        graph[father[i]].push_back(i);
    }

    states = {Tree()};

    for (int i = 1; i <= M; ++ i) {
        int state, q;
        cin >> state >> q;

        states.push_back(states[state]);
        if (q == 1) {
            int u, x;
            cin >> u >> x;
            cout << states.back().add(u, x) << '\n';
        }
        else {
            int u;
            cin >> u;
            states.back().scadUp(father[u], states.back().acorns[u]);
            cout << states.back().reset(u) << '\n';
        }
    }
}

int main()
{
    freopen("data.in", "r", stdin);

    int T = 0;
    cin >> T;
    while (T --)
        test();
    return 0;
}
