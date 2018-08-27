#include <bits/stdc++.h>

using namespace std;

class InputReader {
public:
    InputReader() {}
    InputReader(const char *file_name) {
        input_file = fopen(file_name, "r");
        cursor = 0;
        fread(buffer, SIZE, 1, input_file);
    }
    inline InputReader &operator >>(int &n) {
        while(buffer[cursor] < '0' || buffer[cursor] > '9') {
            advance();
        }
        n = 0;
        while('0' <= buffer[cursor] && buffer[cursor] <= '9') {
            n = n * 10 + buffer[cursor] - '0';
            advance();
        }
        return *this;
    }
private:
    FILE *input_file;
    static const int SIZE = 1 << 17;
    int cursor;
    char buffer[SIZE];
    inline void advance() {
        ++ cursor;
        if(cursor == SIZE) {
            cursor = 0;
            fread(buffer, SIZE, 1, input_file);
        }
    }
};

const int NMAX = 100000 + 5;

int N;
vector <int> tree[NMAX];
int val[NMAX];
int father[NMAX];
int h[NMAX];

double lambda;
typedef long long int lint;

struct Info {
    lint val;
    int h;
    double best;
    Info(lint _val, int _h): val(_val), h(_h), best(val - lambda * h) {}
    Info add(lint _val, int _h) {
        Info res(_val, _h);
        res.best = max(best + _val, _val - lambda * _h);
        return res;
    }
};

vector <Info> stk[NMAX];
void push(vector <Info> &where, lint val, int h) {
    if (where.empty())
        where.emplace_back(val, h);
    else
        where.push_back(where.back().add(val, h));
}
void combine(vector <Info> &from, vector <Info> &to) {
    vector <pair <lint, int> > aux; // (val, h)
    while (!from.empty()) {
        const int h = from.back().h;
        aux.emplace_back(from.back().val + to.back().val, h);
        from.pop_back(), to.pop_back();
    }

    while (!aux.empty()) {
        push(to, aux.back().first, aux.back().second);
        aux.pop_back();
    }
}

double dfs(int node) {
    double ans = -1;
    int largest = -1, who = -1;
    for (auto it: tree[node]) {
        h[it] = 1 + h[node];
        ans = max(ans, dfs(it));
        if (static_cast <int>(stk[it].size()) > largest)
            largest = static_cast <int>(stk[it].size()), who = it;
    }

    if (who != -1)
        stk[node].swap(stk[who]);
    for (auto it: tree[node])
        if (it != who)
            combine(stk[it], stk[node]);
    push(stk[node], val[node], h[node]);

    ans = max(ans, stk[node].back().best + lambda * (h[node] - 1));
    return ans;
}

int main() {
    InputReader cin("craciun.in");
    ofstream cout("craciun.out");

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> val[i];

    for (int i = 2; i <= N; ++ i) {
        cin >> father[i];
        tree[father[i]].push_back(i);
    }

    double l = 0, r = 1E11;
    for (int steps = 0; steps < 60; ++ steps) {
        lambda = (l + r) / 2;
        for (int i = 1; i <= N; ++ i)
            stk[i].clear();
        if (dfs(1) >= 0)
            l = lambda;
        else
            r = lambda;
    }
    cout << fixed << setprecision(12) << l << endl;
    return 0;
}
