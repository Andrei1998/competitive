#include <bits/stdc++.h>

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

//12:31
const int NMAX = 200000 + 5;
struct Node {
    int cnt;
    Node *left, *right;

    Node(): cnt(0), left(NULL), right(NULL) {}
} *roots[NMAX];

Node *mem = new Node[1000000];
int sz;

Node* newNode() {
    if (sz == 1000000) {
        sz = 0;
        mem = new Node[1000000];
    }
    return &mem[sz ++];
}

Node* build(int st, int dr) {
    Node *node = newNode();
    if (st != dr) {
        int mid = (st + dr) >> 1;
        node -> left = build(st, mid);
        node -> right = build(mid + 1, dr);
    }
    return node;
}

Node* add(Node *_node, int where, int nodeSt, int nodeDr) {
    Node *node = newNode();
    *node = *_node;
    ++ node -> cnt;
    if (nodeSt != nodeDr) {
        int mid = (nodeSt + nodeDr) >> 1;
        if (where <= mid)
            node -> left = add(node -> left, where, nodeSt, mid);
        else
            node -> right = add(node -> right, where, mid + 1, nodeDr);
    }
    return node;
}

int query(Node *node, int st, int dr, int nodeSt, int nodeDr) {
    if (st > dr)
        return 0;
    if (nodeSt == st && nodeDr == dr)
        return node -> cnt;
    int mid = (nodeSt + nodeDr) >> 1;
    if (dr <= mid)
        return query(node -> left, st, dr, nodeSt, mid);
    else if (st > mid)
        return query(node -> right, st, dr, mid + 1, nodeDr);
    else
        return query(node -> left, st, mid, nodeSt, mid) +
               query(node -> right, mid + 1, dr, mid + 1, nodeDr);
}
int getLast(Node *node1, Node *node2, int st, int dr) {
    if (st == dr) {
        if (node2 -> cnt - node1 -> cnt)
            return st;
        else
            return 0;
    }
    else if (node2 -> right -> cnt - node1 -> right -> cnt)
        return getLast(node1 -> right, node2 -> right, ((st + dr) >> 1) + 1, dr);
    else
        return getLast(node1 -> left, node2 -> left, st, (st + dr) >> 1);
}

int N, K;
int A[NMAX];
int B[NMAX];
int T[NMAX];

vector <int> allVals;
vector <int> freq[NMAX];

int main()
{
    //ios_base :: sync_with_stdio(false);
    //freopen("data.in", "r", stdin);
    InputReader cin;

    cin >> N >> K;

    for (int i = 1; i <= N; ++ i)
        cin >> A[i] >> B[i];

    for (int i = 1; i <= K; ++ i) {
        cin >> T[i];
        allVals.push_back(T[i]);
    }

    sort(allVals.begin(), allVals.end());
    allVals.resize(unique(allVals.begin(), allVals.end()) - allVals.begin());

    for (int i = 1; i <= K; ++ i) {
        T[i] = lower_bound(allVals.begin(), allVals.end(), T[i]) - allVals.begin() + 1;
        freq[T[i]].push_back(i);
    }

    roots[0] = build(1, K);
    for (int i = 1; i <= static_cast <int>(allVals.size()); ++ i) {
        roots[i] = roots[i - 1];
        for (auto it: freq[i])
            roots[i] = add(roots[i], it, 1, K);
    }

    long long int ans = 0;
    for (int i = 1; i <= N; ++ i) {
        int a = min(A[i], B[i]);
        int b = max(A[i], B[i]);

        a = lower_bound(allVals.begin(), allVals.end(), a) - allVals.begin();
        b = lower_bound(allVals.begin(), allVals.end(), b) - allVals.begin();

        int pos = getLast(roots[a], roots[b], 1, K);

        bool rev = false;
        if (pos == 0) {
            if (A[i] < B[i])
                rev = true;
        }

        int cnt = query(roots[allVals.size()], pos + 1, K, 1, K) - query(roots[b], pos + 1, K, 1, K);
        if (cnt % 2 == rev)
            ans += max(A[i], B[i]);
        else
            ans += min(A[i], B[i]);
    }

    cout << ans << '\n';
    return 0;
}
