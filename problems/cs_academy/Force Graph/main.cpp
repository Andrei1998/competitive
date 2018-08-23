#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100000 + 5;

int N, F1, F2;
vector <int> graph[NMAX];

struct Point {
    int x, y;
} points[NMAX];

typedef long long int lint;
lint ansx[NMAX];
lint ansy[NMAX];

int main() {
    freopen("data.in", "r", stdin);

    int M = 0;
    cin >> N >> M >> F1 >> F2;

    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= N; ++ i)
        cin >> points[i].x >> points[i].y;

    //Solve x
    lint sumX = 0;
    lint sumY = 0;
    for (int i = 1; i <= N; ++ i) {
        sumX += 1LL * F2 * points[i].x;
        sumY += 1LL * F2 * points[i].y;
    }

    for (int i = 1; i <= N; ++ i) {
        ansx[i] = sumX - 1LL * F2 * N * points[i].x;
        ansy[i] = sumY - 1LL * F2 * N * points[i].y;
    }

    //Rectify all edges
    for (int i = 1; i <= N; ++ i)
        for (auto it: graph[i]) {
            ansx[i] -= 1LL * (points[i].x - points[it].x) * (F1 - F2);
            ansy[i] -= 1LL * (points[i].y - points[it].y) * (F1 - F2);
        }

    for (int i = 1; i <= N; ++ i)
        cout << -ansx[i] << ' ' << -ansy[i] << '\n';
    return 0;
}
