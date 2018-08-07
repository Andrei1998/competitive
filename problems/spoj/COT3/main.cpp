#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

struct Trie {
    int h;
    int lazy;
    bool full, word;
    Trie *alf[2];

    Trie(int _h): h(_h) {
        lazy = full = word = false;
        alf[0] = alf[1] = NULL;
    }

    void makeLazy(int val) {
        lazy ^= val;
        if (val & (1 << h))
            swap(alf[0], alf[1]);
    }

    void propagate() {
        if (lazy) {
            if (alf[0] != NULL)
                alf[0] -> makeLazy(lazy & (~(1 << h)));
            if (alf[1] != NULL)
                alf[1] -> makeLazy(lazy & (~(1 << h)));
            lazy = 0;
        }
    }

    inline void compute() {
        full = (alf[0] != NULL && alf[0] -> full && alf[1] != NULL && alf[1] -> full);
    }
};

int getMex(Trie *t, int nr) {
    t -> propagate();

    if (t -> alf[0] == NULL)
        return nr;
    else if (!(t -> alf[0] -> full))
        return getMex(t -> alf[0], nr);
    else if (t -> alf[1] == NULL)
        return nr + (1 << (t -> h));
    else
        return getMex(t -> alf[1], nr + (1 << (t -> h)));
}

void insert(Trie *t, int nr) {
    if (t -> h == -1) {
        t -> word = t -> full = true;
        return ;
    }

    bool bit = 0;
    if (nr & (1 << (t -> h)))
        bit = 1;

    if (t -> alf[bit] == NULL)
        t -> alf[bit] = new Trie(t -> h - 1);
    insert(t -> alf[bit], nr);
    t -> compute();
}

void dfsInsert(Trie *from, Trie *to) {
    if (from -> h == -1) {
        to -> word |= from -> word;
        to -> full |= from -> full;
        delete from;
        return ;
    }

    from -> propagate();
    to -> propagate();

    for (int i = 0; i < 2; ++ i)
        if (from -> alf[i] != NULL) {
            if (to -> alf[i] == NULL)
                to -> alf[i] = new Trie(to -> h - 1);
            dfsInsert(from -> alf[i], to -> alf[i]);
        }

    to -> compute();
    delete from;
}

const int NMAX = 100000 + 5;

int N;
bool c[NMAX];
vector <int> graph[NMAX];
int sz[NMAX];

int sp[NMAX];
int z[NMAX];
Trie *tries[NMAX];

void dfs(int node, int father) {
    int maximum = -1, maxSon;
    for (auto it: graph[node])
        if (it != father) {
            dfs(it, node);
            sz[node] += sz[it];
            z[node] ^= sp[it];

            if (sz[it] > maximum) {
                maximum = sz[it];
                maxSon = it;
            }
        }
    ++sz[node];

    for (auto it: graph[node])
        if (it != father)
            tries[it] -> makeLazy(z[node] ^ sp[it]);

    if (maximum == -1)
        tries[node] = new Trie(16);
    else
        tries[node] = tries[maxSon];

    for (auto it: graph[node])
        if (it != father && it != maxSon)
            dfsInsert(tries[it], tries[node]);

    if (c[node] == 0)
        insert(tries[node], z[node]);
    sp[node] = getMex(tries[node], 0);
}

vector <int> sol;

void dfsSol(int node, int father, int val) {
    if (!c[node] && !val)
        sol.push_back(node);

    for (auto it: graph[node])
        if (it != father)
            dfsSol(it, node, val ^ sp[it] ^ z[it]);
}

int main()
{
    ios_base :: sync_with_stdio(false);
    //freopen("data.in", "r", stdin);

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> c[i];

    for (int i = 1; i < N; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1, 0);
    dfsSol(1, 0, z[1]);

    if (sol.empty())
        cout << "-1\n";
    else {
        sort(sol.begin(), sol.end());
        for (int i = 0; i < sol.size(); ++ i)
            cout << sol[i] << '\n';
    }
    return 0;
}
