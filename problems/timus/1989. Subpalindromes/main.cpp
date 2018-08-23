#include <iostream>
#include <cstdio>
#include <cctype>
#include <string>

using namespace std;

class InputReader {
public:
    InputReader() {
        input_file = stdin;
        cursor = 0;
        fread(buffer, SIZE, 1, input_file);
    }
    inline InputReader &operator>>(int &n) {
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
    inline InputReader &operator>>(char &n) {
        while(buffer[cursor] < 'a' || buffer[cursor] > 'z')
            advance();
        n = buffer[cursor];
        advance();
        return *this;
    }
    inline InputReader &operator>>(string &n) {
        while (isspace(buffer[cursor]))
            advance();
        n = "";
        while(!isspace(buffer[cursor])) {
            n += buffer[cursor];
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

typedef unsigned long long int ulint;

//int MOD[] = {1000000000 + 7, 1000000000 + 9};

/*struct Hash {
    int h[sizeof(MOD) / sizeof(int)];

    Hash() {
        for (int i = 0; i < sizeof(MOD) / sizeof(int); ++ i)
            h[i] = 0;
    }

    //Warning: Not generic
    Hash(int h0, int h1) {
        h[0] = h0;
        h[1] = h1;
    }

    Hash operator+(const Hash &arg) const {
        Hash res;
        for (int i = 0; i < sizeof(MOD) / sizeof(int); ++ i) {
            res.h[i] = h[i] + arg.h[i];
            if (res.h[i] >= MOD[i])
                res.h[i] -= MOD[i];
        }
        return res;
    }

    Hash operator*(const Hash &arg) const {
        Hash res;
        for (int i = 0; i < sizeof(MOD) / sizeof(int); ++ i)
            res.h[i] = (1LL * h[i] * arg.h[i]) % MOD[i];
        return res;
    }

    bool operator==(const Hash &arg) {
        for (int i = 0; i < sizeof(MOD) / sizeof(int); ++ i)
            if (h[i] != arg.h[i])
                return false;
        return true;
    }
};*/

const int NMAX = 100000 + 5;
//const Hash C = {666013, 666017};
ulint C = 666013;

ulint powC[NMAX];

struct Node {
    int st, dr;
    ulint h, hRev;
} tree[4 * NMAX];

void unite(Node &res, const Node a, const Node &b) {
    if (a.dr == -1) {
        res = b;
        return ;
    }

    res.dr = b.dr;

    res.h    = a.h * powC[b.dr - b.st + 1] + b.h;
    res.hRev = b.hRev * powC[a.dr - a.st + 1] + a.hRev;
}

string str;
void build(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;
    if (st == dr) {
        tree[node].h = tree[node].hRev = str[st];
        return ;
    }

    int mid = (tree[node].st + tree[node].dr) >> 1;
    build(node << 1, st, mid);
    build((node << 1) + 1, mid + 1, dr);

    unite(tree[node], tree[node << 1], tree[(node << 1) + 1]);
}

void update(int node, int where) {
    if (tree[node].st == tree[node].dr) {
        tree[node].h = tree[node].hRev = str[where];
        return ;
    }

    int mid = (tree[node].st + tree[node].dr) >> 1;

    if (where <= mid)
        update(node << 1 ,where);
    else
        update((node << 1) + 1, where);
    unite(tree[node], tree[node << 1], tree[(node << 1) + 1]);
}

void query(int node, int l, int r, Node &res) {
    if (tree[node].st == l && tree[node].dr == r) {
        unite(res, res, tree[node]);
        return ;
    }

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (r <= mid)
        query(node << 1, l, r, res);
    else if (l > mid)
        query((node << 1) + 1, l, r, res);
    else {
        query(node << 1, l, mid, res);
        query((node << 1) + 1, mid + 1, r, res);
    }
}

int main()
{
    //ios_base :: sync_with_stdio(false);
    InputReader cin;

    cin >> str;
    int N = str.size();
    str = " " + str;

    powC[0] = 1;
    for (int i = 1; i <= N; ++ i)
        powC[i] = C * powC[i - 1];

    build(1, 1, N);

    int q = 0;
    cin >> q;

    while (q --) {
        string qry;
        cin >> qry;

        if (qry == "change") {
            int where;
            char ch;

            cin >> where >> ch;
            str[where] = ch;
            update(1, where);
        }
        else {
            int l, r;
            cin >> l >> r;

            Node ans;
            ans.dr = -1;

            query(1, l, r, ans);

            if (ans.h == ans.hRev)
                cout << "Yes\n";
            else
                cout << "No\n";
        }
    }

    return 0;
}
