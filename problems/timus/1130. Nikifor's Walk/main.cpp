#include <iostream>
#include <complex>
#include <vector>
#include <cstdlib>

using namespace std;

typedef complex <int> Point;

const int NMAX = 10000 + 5;

int N, L;
bool ok(const Point &sum) {
    return norm(sum) <= L * L;
}

bool ok2(const Point &sum) {
    return norm(sum) <= 2 * L * L;
}

Point v[2 * NMAX];
vector <int> graph[2 * NMAX];
bool sign[2 * NMAX];

int act[NMAX];
int nodes, cnt;

void add(int ind1, int ind2, int ind3, bool sign1, bool sign2, Point sum) {
    ++ nodes;
    v[nodes] = sum;

    graph[nodes].push_back(ind1);
    graph[nodes].push_back(ind2);
    sign[ind1] ^= sign1;
    sign[ind2] ^= sign2;

    act[++ cnt] = nodes;
    if (ind3)
        act[++ cnt] = ind3;
}

void dfs(int node) {
    for (auto it: graph[node]) {
        sign[it] ^= sign[node];
        dfs(it);
    }
}

int main()
{
    cin >> N >> L;
    for (int i = 1; i <= N; ++ i) {
        int x, y;
        cin >> x >> y;
        v[i] = Point(x, y);
        act[i] = i;
    }

    nodes = N;
    cnt = N;

    while (cnt > 1)
        if (cnt > 2) {
            int ind1 = act[cnt];
            Point p1 = v[ind1];
            int ind2 = act[cnt - 1];
            Point p2 = v[ind2];
            int ind3 = act[cnt - 2];
            Point p3 = v[ind3];
            cnt -= 3;

            if (ok(p1 + p2))
                add(ind1, ind2, ind3, 0, 0, p1 + p2);
            else if (ok(p1 - p2))
                add(ind1, ind2, ind3, 0, 1, p1 - p2);
            else if (ok(-p1 + p2))
                add(ind1, ind2, ind3, 1, 0, -p1 + p2);
            else if (ok(-p1 - p2))
                add(ind1, ind2, ind3, 1, 1, -p1 - p2);

            else if (ok(p1 + p3))
                add(ind1, ind3, ind2, 0, 0, p1 + p3);
            else if (ok(p1 - p3))
                add(ind1, ind3, ind2, 0, 1, p1 - p3);
            else if (ok(-p1 + p3))
                add(ind1, ind3, ind2, 1, 0, -p1 + p3);
            else if (ok(-p1 - p3))
                add(ind1, ind3, ind2, 1, 1, -p1 - p3);

            else if (ok(p2 + p3))
                add(ind2, ind3, ind1, 0, 0, p2 + p3);
            else if (ok(p2 - p3))
                add(ind2, ind3, ind1, 0, 1, p2 - p3);
            else if (ok(-p2 + p3))
                add(ind2, ind3, ind1, 1, 0, -p2 + p3);
            else if (ok(-p2 - p3))
                add(ind2, ind3, ind1, 1, 1, -p2 - p3);
            else {
                return -1;
            }
        }
        else {
            int ind1 = act[1];
            Point p1 = v[ind1];
            int ind2 = act[2];
            Point p2 = v[ind2];
            cnt -= 2;

            if (ok2(p1 + p2))
                add(ind1, ind2, 0, 0, 0, p1 + p2);
            else if (ok2(p1 - p2))
                add(ind1, ind2, 0, 0, 1, p1 - p2);
            else if (ok2(-p1 + p2))
                add(ind1, ind2, 0, 1, 0, -p1 + p2);
            else if (ok2(-p1 - p2))
                add(ind1, ind2, 0, 1, 1, -p1 - p2);
            else {
                return -1;
            }
        }

    dfs(act[1]);

    cout << "YES\n";
    for (int i = 1; i <= N; ++ i)
        if (sign[i] == 0)
            cout << '+';
        else
            cout << '-';
    cout << '\n';
    return 0;
}
