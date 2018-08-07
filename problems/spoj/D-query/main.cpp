#include <iostream>
#include <cstdio>

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

const int NMAX = 30000 + 5;
const int NODESMAX = 2 * 17 * NMAX;
const int VALMAX = 1e6 + 5;

struct Node {
    int st, dr;
    int sum;
    int left, right;

    Node(int _st = 0, int _dr = 0, int _sum = 0, int _left = 0, int _right = 0):
        st(_st), dr(_dr), sum(_sum), left(_left), right(_right) {}
} tree[NODESMAX];

int treeCnt;

int build(int st, int dr) {
    int node = ++ treeCnt;

    if (st == dr)
        tree[node] = Node(st, dr);
    else {
        int mid = (st + dr) >> 1;
        tree[node] = Node(st, dr, 0, build(st, mid), build(mid + 1, dr));
    }

    return node;
}

int update(int _node, int where, int val) {
    int node = ++ treeCnt;
    tree[node] = tree[_node];

    tree[node].sum += val;

    if (tree[node].st == tree[node].dr)
        return node;

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (where <= mid)
        tree[node].left = update(tree[node].left, where, val);
    else
        tree[node].right = update(tree[node].right, where, val);
    return node;
}

int query(int node, int where) {
    if (tree[node].st == where)
        return tree[node].sum;

    int mid = (tree[node].st + tree[node].dr) >> 1;

    if (where > mid)
        return query(tree[node].right, where);
    else
        return tree[tree[node].right].sum + query(tree[node].left, where);
}

int lastApp[VALMAX];
int treeAtMoment[NMAX];

int main()
{
    InputReader cin;

    int n;
    cin >> n;

    treeAtMoment[0] = build(1, n);
    for (int i = 1; i <= n; ++ i) {
        treeAtMoment[i] = treeAtMoment[i - 1];

        int val = 0;
        cin >> val;

        if (lastApp[val])
            treeAtMoment[i] = update(treeAtMoment[i], lastApp[val], -1);
        lastApp[val] = i;
        treeAtMoment[i] = update(treeAtMoment[i], lastApp[val], 1);
    }

    int q = 0;
    cin >> q;

    while (q --) {
        int x, y;
        cin >> x >> y;
        cout << query(treeAtMoment[y], x) << '\n';
    }
    return 0;
}
