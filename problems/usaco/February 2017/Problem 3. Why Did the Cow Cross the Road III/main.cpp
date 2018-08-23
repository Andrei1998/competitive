#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

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

class AIB {
public:
    vector <int> aib;

    inline void build(int N) {
        aib.resize(N + 1);
    }

    inline int lsb(int node) {
        return node & (-node);
    }

    void add(int where) {
        for (; where < aib.size(); where += lsb(where))
            ++ aib[where];
    }

    int query(int where) {
        int ans = 0;
        for (; where; where -= lsb(where))
            ans += aib[where];
        return ans;
    }
};

const int NMAX = 100000 + 5;

typedef long long int lint;

int N;
int orderedA[NMAX];
int a[NMAX];
int whereB[NMAX];

struct Node2D {
    int st, dr;
    vector <int> vals;
    AIB aib;
} tree[4 * NMAX];

void build2D(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;
    if (st == dr)
        return ;

    int mid = (st + dr) >> 1;
    build2D(node << 1, st, mid);
    build2D((node << 1) + 1, mid + 1, dr);
}

void update2DPrepareAIB(int node, int where, int y) {
    tree[node].vals.push_back(y);
    if (tree[node].st == tree[node].dr)
        return ;

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (where <= mid)
        update2DPrepareAIB(node << 1, where, y);
    else
        update2DPrepareAIB((node << 1) + 1, where, y);
}

void build2DPrepareAIB(int node) {
    vector <int> &v = tree[node].vals;
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    tree[node].aib.build(v.size());

    if (tree[node].st == tree[node].dr)
        return ;

    build2DPrepareAIB(node << 1);
    build2DPrepareAIB((node << 1) + 1);
}

void update2D(int node, int where, int y) {
    vector <int> &v = tree[node].vals;

    tree[node].aib.add(lower_bound(v.begin(), v.end(), y) - v.begin() + 1);
    if (tree[node].st == tree[node].dr)
        return ;

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (where <= mid)
        update2D(node << 1, where, y);
    else
        update2D((node << 1) + 1, where, y);
}

int query2D(int node, int st, int dr, int y0, int y1) {
    if (y0 > y1)
        return 0;

    if (tree[node].st == st && tree[node].dr == dr) {
        vector <int> &v = tree[node].vals;
        return tree[node].aib.query(upper_bound(v.begin(), v.end(), y1) - v.begin()) -
               tree[node].aib.query(upper_bound(v.begin(), v.end(), y0 - 1) - v.begin());
    }

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (dr <= mid)
        return query2D(node << 1, st, dr, y0, y1);
    else if (st > mid)
        return query2D((node << 1) + 1, st, dr, y0, y1);
    else
        return query2D(node << 1, st, mid, y0, y1) +
               query2D((node << 1) + 1, mid + 1, dr, y0, y1);
}

int main()
{
    InputReader cin("friendcross.in");
    ofstream cout("friendcross.out");

    int K;
    cin >> N >> K;

    for (int i = 1; i <= N; ++ i)
        cin >> a[i];

    for (int i = 1; i <= N; ++ i) {
        int aux;
        cin >> aux;
        whereB[aux] = i;
    }
    for (int i = 1; i <= N; ++ i)
        orderedA[i] = whereB[a[i]];

    build2D(1, 1, N);
    for (int i = 1; i <= N; ++ i)
        update2DPrepareAIB(1, orderedA[i], a[i]);
    build2DPrepareAIB(1);

    lint ans = 0;
    for (int i = 1; i <= N; ++ i) {
        ans += query2D(1, orderedA[i], N, a[i] + K + 1, N);
        ans += query2D(1, orderedA[i], N, 1, a[i] - K - 1);

        update2D(1, orderedA[i], a[i]);
    }

    cout << ans << '\n';
    return 0;
}
