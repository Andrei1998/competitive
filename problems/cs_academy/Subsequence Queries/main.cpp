#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MOD = 1000000000 + 7;

class Matrix {
public:
    static const int N = 10;

    Matrix(int c = 0) {
        memset(mat, 0, sizeof mat);
        for (int i = 0; i < N; ++ i)
            mat[i][i] = c;
    }

    int mat[N][N];

    Matrix operator*(const Matrix &arg) const {
        Matrix ans;
        for (int i = 0; i < N; ++ i)
            for (int j = 0; j < N; ++ j) {
                unsigned long long int aux = 0;
                for (int k = 0; k < N; ++ k)
                    aux += 1ULL * mat[i][k] * arg.mat[k][j];
                ans.mat[i][j] = aux % MOD;
            }
        return ans;
    }
} ch[10];

const int NMAX = 30000 + 5;
struct Node {
    int st, dr;
    Matrix prod;
} tree[4 * NMAX];

int N;
string str;

void build(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;

    if (st == dr) {
        tree[node].prod = ch[str[st] - 'a'];
        return ;
    }

    int mid = (st + dr) >> 1;
    build(node << 1, st, mid);
    build((node << 1) + 1, mid + 1, dr);

    tree[node].prod = tree[node << 1].prod * tree[(node << 1) + 1].prod;
}

int ans[10];
unsigned long long int ans2[10];
void query(int node, int st, int dr) {
    if (tree[node].st == st && tree[node].dr == dr) {

        for (int i = 0; i < 10; ++ i) {
            ans2[i] = 0;
            for (int j = 0; j < 10; ++ j)
                ans2[i] += 1ULL * tree[node].prod.mat[i][j] * ans[j];
        }

        for (int i = 0; i < 10; ++ i)
            ans[i] = ans2[i] % MOD;
        return ;
    }

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (dr <= mid)
        query(node << 1, st, dr);
    else if (st > mid)
        query((node << 1) + 1, st, dr);
    else {
        query((node << 1) + 1, mid + 1, dr);
        query(node << 1, st, mid);
    }
}

int main()
{
    for (int i = 0; i < 10; ++ i)
        ch[0].mat[i][i] = 1;
    for (int i = 0; i < 10; ++ i)
        ch[i] = ch[0];

    for (int i = 0; i < 10; ++ i)
        for (int j = 0; j < 10; ++ j)
            ch[i].mat[i][j] = 1;

    cin >> str;
    N = str.size();
    str = " " + str;

    build(1, 1, N);

    int Q = 0;
    cin >> Q;

    while (Q --) {
        int l, r;
        cin >> l >> r;
        for (int i = 0; i < 10; ++ i)
            ans[i] = 0;
        ans[9] = 1;
        query(1, l, r);

        int res = 0;
        for (int i = 0; i < 9; ++ i) {
            res += ans[i];
            if (res >= MOD)
                res -= MOD;
        }
        cout << res << '\n';
    }

    return 0;
}
