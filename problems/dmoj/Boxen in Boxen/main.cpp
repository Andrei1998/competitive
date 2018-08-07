#include <iostream>
#include <cassert>
#include <algorithm>
#include <set>

#define lint long long int
using namespace std;

const int NMAX = 1e5 + 5;
const int MOD1 = 1000000000 + 7;
const int MOD2 = 1000000000 + 9;
const int MOD3 = 1000000000 + 21;

int N, F;

struct Box {
    int a, b;
    int pos;

    friend bool operator<(const Box &a, const Box &b) {
        return a.b * (b.a - 1LL) < b.b * (a.a - 1LL);
    }
} boxes[NMAX];

int whereUpd[NMAX];

template <int MOD>
struct Matrix {
    int mat[2][2];

    Matrix(int c = 0) {
        mat[0][0] = mat[1][1] = c;
        mat[0][1] = mat[1][0] = 0;
    }

    Matrix(int a, int b, int c, int d) {
        mat[0][0] = a;
        if (b < 0)
            b += MOD;
        mat[0][1] = b;
        mat[1][0] = c;
        mat[1][1] = d;
    }

    //B * A
    friend Matrix operator*(const Matrix &a, const Matrix &b) {
        Matrix res;
        for (int i = 0; i < 2; ++ i)
            for (int j = 0; j < 2; ++ j)
                for (int k = 0; k < 2; ++ k)
                    res.mat[i][j] = (res.mat[i][j] + 1LL * b.mat[i][k] * a.mat[k][j]) % MOD;
        return res;
    }

    int apply(int x) {
        return (1LL * mat[0][0] * x + mat[0][1]) % MOD;
    }
};

struct Node {
    int st, dr;
    Matrix <MOD1> prod1;
    Matrix <MOD2> prod2;
    Matrix <MOD3> prod3;
} tree[4 * NMAX];

void build(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;
    tree[node].prod1 = Matrix <MOD1>(1);
    tree[node].prod2 = Matrix <MOD2>(1);
    tree[node].prod3 = Matrix <MOD3>(1);

    if (st == dr)
        return ;

    int mid = (tree[node].st + tree[node].dr) >> 1;

    build(node << 1, st, mid);
    build((node << 1) + 1, mid + 1, dr);
}

void activate(int node, int where) {
    if (tree[node].st == tree[node].dr) {
        tree[node].prod1 = Matrix <MOD1>(boxes[where].a, -boxes[where].b, 0, 1);
        tree[node].prod2 = Matrix <MOD2>(boxes[where].a, -boxes[where].b, 0, 1);
        tree[node].prod3 = Matrix <MOD3>(boxes[where].a, -boxes[where].b, 0, 1);
        return ;
    }

    int mid = (tree[node].st + tree[node].dr) >> 1;

    if (where <= mid)
        activate(node << 1, where);
    else
        activate((node << 1) + 1, where);

    tree[node].prod1 = tree[node << 1].prod1 * tree[(node << 1) + 1].prod1;
    tree[node].prod2 = tree[node << 1].prod2 * tree[(node << 1) + 1].prod2;
    tree[node].prod3 = tree[node << 1].prod3 * tree[(node << 1) + 1].prod3;
}

Matrix <MOD1> ans1;
Matrix <MOD2> ans2;
Matrix <MOD3> ans3;

void query(int node, int dr) {
    if (dr < tree[node].st)
        return ;

    if (tree[node].dr == dr) {
        ans1 = ans1 * tree[node].prod1;
        ans2 = ans2 * tree[node].prod2;
        ans3 = ans3 * tree[node].prod3;
        return ;
    }

    int mid = (tree[node].st + tree[node].dr) >> 1;

    if (dr <= mid)
        query(node << 1, dr);
    else {
        query(node << 1, mid);
        query((node << 1) + 1, dr);
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    //ifstream cin("data.in");
    //ofstream cout("data.out");

    cin >> N >> F;

    for (int i = 1; i <= N; ++ i) {
        cin >> boxes[i].a >> boxes[i].b;
        boxes[i].pos = i;
    }
    sort(boxes + 1, boxes + N + 1);

    for (int i = 1; i <= N; ++ i)
        whereUpd[boxes[i].pos] = i;

    build(1, 1, N);

    set <int> indices;
    indices.insert(0);

    set <int> :: iterator it = indices.begin();

    for (int i = 1; i <= N; ++ i) {
        indices.insert(whereUpd[i]);
        activate(1, whereUpd[i]);

        ans1 = Matrix <MOD1>(1);
        ans2 = Matrix <MOD2>(1);
        ans3 = Matrix <MOD3>(1);

        query(1, *it);

        int v1 = ans1.apply(F);
        int v2 = ans2.apply(F);
        int v3 = ans3.apply(F);

        while (1) {
            ++ it;
            if (it != indices.end()) {
                if (boxes[*it].a != 1 && (v1 != v2 || v1 != v3 || v1 * (boxes[*it].a - 1LL) >= boxes[*it].b)) {
                    //Add
                    ans1 = Matrix <MOD1>(1);
                    ans2 = Matrix <MOD2>(1);
                    ans3 = Matrix <MOD3>(1);

                    query(1, *it);

                    v1 = ans1.apply(F);
                    v2 = ans2.apply(F);
                    v3 = ans3.apply(F);
                }
                else {
                    -- it;
                    break;
                }
            }
            else {
                -- it;
                break;
            }
        }

        cout << v1 << '\n';
    }

    //cin.close();
    //cout.close();
    return 0;
}

/*
Failed on this:
8 3
29 18
71 90
85 35
89 63
25 87
1 99
8 1
53 93
*/
