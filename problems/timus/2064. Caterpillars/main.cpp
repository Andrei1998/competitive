#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

class InputReader {
public:
    InputReader() {
        input_file = stdin;
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

const int VALMAX = 1000000 + 5;
const int INF = 2E9 + 15;

int ans[VALMAX];

struct Node {
    int st, dr;
    int maximumUp;
    int maximumDown;
} tree[4 * VALMAX];

void build(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;
    tree[node].maximumUp = tree[node].maximumDown = -INF;

    if (st == dr)
        return ;

    int mid = (tree[node].st + tree[node].dr) >> 1;
    build(node << 1, st, mid);
    build((node << 1) + 1, mid + 1, dr);
}

void updateUp(int node, int st, int dr, int val, int valUp) {
    valUp = max(valUp, tree[node].maximumUp);
    if (val < valUp)
        return ;

    if (tree[node].st == st && tree[node].dr == dr) {
        tree[node].maximumUp = val;
        return ;
    }

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (dr <= mid)
        updateUp(node << 1, st, dr, val, valUp);
    else if (st > mid)
        updateUp((node << 1) + 1, st, dr, val, valUp);
    else {
        updateUp(node << 1, st, mid, val, valUp);
        updateUp((node << 1) + 1, mid + 1, dr, val, valUp);
    }
}

void updateDown(int node, int st, int dr, int val, int valDown) {
    valDown = max(valDown, tree[node].maximumDown);
    if (val < valDown)
        return ;

    if (tree[node].st == st && tree[node].dr == dr) {
        tree[node].maximumDown = val;
        return ;
    }

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (dr <= mid)
        updateDown(node << 1, st, dr, val, valDown);
    else if (st > mid)
        updateDown((node << 1) + 1, st, dr, val, valDown);
    else {
        updateDown(node << 1, st, mid, val, valDown);
        updateDown((node << 1) + 1, mid + 1, dr, val, valDown);
    }
}

void update(int t) {
    bool par = 0;
    int where = 0;
    while (where <= 1000000) {
        if (!par)
            updateUp(1, where, min(1000000, where + t), -where, -INF);
        else
            updateDown(1, where, min(1000000, where + t), where + t, -INF);

        where += t;
        par ^= 1;
    }
}

void finalize(int node, int valUp, int valDown) {
    valUp = max(valUp, tree[node].maximumUp);
    valDown = max(valDown, tree[node].maximumDown);

    if (tree[node].st == tree[node].dr) {
        ans[tree[node].st] = max(valUp + tree[node].st, valDown - tree[node].st);
        return ;
    }

    finalize(node << 1, valUp, valDown);
    finalize((node << 1) + 1, valUp, valDown);
}

int main()
{
    InputReader cin;
    //ios_base :: sync_with_stdio(false);
    //cin.tie(0);

    int N = 0;
    cin >> N;

    vector <int> caterpillars(N);

    //for (int i = 0; i < N; ++ i)
    //    caterpillars[i] = i + 1;

    for (int i = 0; i < N; ++ i)
        cin >> caterpillars[i];
    sort(caterpillars.begin(), caterpillars.end());
    caterpillars.resize(unique(caterpillars.begin(), caterpillars.end()) - caterpillars.begin());

    reverse(caterpillars.begin(), caterpillars.end());

    //Build structure
    build(1, 0, 1000000);
    for (auto it: caterpillars)
        update(it);

    finalize(1, -INF, -INF);

    int Q = 0;
    cin >> Q;

    while (Q --) {
        int x;
        cin >> x;
        cout << ans[x] << '\n';
    }
    return 0;
}
