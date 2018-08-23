#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#define lint long long int
using namespace std;

const int NMAX = 200 + 5;

int N, M;
pair <int, int> edges[NMAX];

vector <int> graph[NMAX];

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0):
        x(_x), y(_y) {}
} p[NMAX];

lint ccw(const Point &a, const Point &refer, const Point &b) {
    return 1LL * (a.x - refer.x) * (b.y - refer.y) - 1LL * (a.y - refer.y) * (b.x - refer.x);
}

int sgn(lint x) {
    if (x < 0)
        return -1;
    else if (x > 0)
        return 1;
    else
        return 0;
}

bool inters(const Point &A, const Point &B, const Point &C, const Point &D) {
    int minX1 = min(A.x, B.x);
    int minX2 = min(C.x, D.x);
    int maxX1 = max(A.x, B.x);
    int maxX2 = max(C.x, D.x);
    int minY1 = min(A.y, B.y);
    int minY2 = min(C.y, D.y);
    int maxY1 = max(A.y, B.y);
    int maxY2 = max(C.y, D.y);

    if (minX1 > maxX2)
        return false;
    if (minX2 > maxX1)
        return false;
    if (minY1 > maxY2)
        return false;
    if (minY2 > maxY1)
        return false;

    if (sgn(ccw(A, B, C)) * sgn(ccw(A, B, D)) > 0)
        return false;
    if (sgn(ccw(C, D, A)) * sgn(ccw(C, D, B)) > 0)
        return false;
    return true;
}

bool vis[NMAX];
void dfs(int node) {
    vis[node] = true;
    for (auto it: graph[node])
        if (!vis[it])
            dfs(it);
}

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 1; i <= N; ++ i)
        cin >> p[i].x >> p[i].y;
    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;

        edges[i] = {a, b};

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= M; ++ i) {
        //Segm - segm
        for (int j = i + 1; j <= M; ++ j)
            if (inters(p[edges[i].first], p[edges[i].second],
                       p[edges[j].first], p[edges[j].second])) {
                graph[edges[i].first].push_back(edges[j].second);
                graph[edges[j].second].push_back(edges[i].first);
            }

        //Segm - point
        for (int j = 1; j <= N; ++ j)
            if (inters(p[edges[i].first], p[edges[i].second],
                       p[j], p[j])) {
                graph[edges[i].first].push_back(j);
                graph[j].push_back(edges[i].first);
            }
    }
    dfs(1);
    for (int i = 1; i <= N; ++ i)
        if (!vis[i]) {
            cout << "NO\n";
            return 0;
        }
    cout << "YES\n";
    return 0;
}
