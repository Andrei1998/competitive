#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 100000 + 5;
const int MMAX = 2 * NMAX;

int father[NMAX][17];
int h[NMAX];

int lca(int a, int b) {
    if (h[a] > h[b])
        swap(a, b);

    for (int i = 16; i >= 0; -- i)
        if (father[b][i] && h[father[b][i]] >= h[a])
            b = father[b][i];

    if (a == b)
        return a;

    for (int i = 16; i >= 0; -- i)
        if (father[a][i] != father[b][i]) {
            a = father[a][i];
            b = father[b][i];
        }

    return father[a][0];
}

inline int dist(int a, int b) {
    return h[a] + h[b] - 2 * h[lca(a, b)];
}

void add(int node, int f) {
    h[node] = 1 + h[f];
    father[node][0] = f;
    for (int i = 1; i < 17; ++ i)
        father[node][i] = father[father[node][i - 1]][i - 1];
}

struct Elem {
    int d;
    int A, B;

    Elem(int _d, int _A, int _B, bool nope = false): d(_d), A(_A), B(_B) {
        if (!nope && A > B)
            swap(A, B);
    }

    friend bool operator>(const Elem &a, const Elem &b) {
        if (a.d != b.d)
            return a.d > b.d;
        else if (a.A != b.A)
            return a.A < b.A;
        else
            return a.B < b.B;
    }
};

int main()
{
    ios_base :: sync_with_stdio(false);
    //freopen("data.in", "r", stdin);

    int N, M;
    cin >> N >> M;

    Elem diam(0, 1, 1);
    while (M--) {
        char op;
        cin >> op;

        if (op == 'U') {
            int x, y;
            cin >> y >> x;
            add(x, y);

            for (auto it: {Elem(dist(x, diam.A), x, diam.A), Elem(dist(x, diam.B), x, diam.B)})
                if (it > diam)
                    diam = it;
        }
        else {
            int x;
            cin >> x;

            Elem e1(dist(x, diam.A), x, diam.A, true);
            Elem e2(dist(x, diam.B), x, diam.B, true);

            if (e1 > e2)
                cout << e1.d << ' ' << e1.B << '\n';
            else
                cout << e2.d << ' ' << e2.B << '\n';
        }
    }
    return 0;
}
