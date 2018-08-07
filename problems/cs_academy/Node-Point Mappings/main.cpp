#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <numeric>

using namespace std;

const int NMAX = 1000 + 5;
const int INF = 1E9 + 15;

vector <int> graph[NMAX];

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0):
        x(_x), y(_y) {}
    friend bool operator==(const Point &a, const Point &b) {
        return a.x == b.x && a.y == b.y;
    }
} points[NMAX];

int whichPct[NMAX];

Point rf;
bool cmp(const int &a, const int &b) {
    Point A = points[a];
    Point B = points[b];
    return atan2(A.y - rf.y, A.x - rf.x) < atan2(B.y - rf.y, B.x - rf.x);
}

bool operator<(const Point &a, const Point &b) {
    if (a.x != b.x)
        return a.x < b.x;
    else
        return a.y < b.y;
}

int sz[NMAX];
void dfs(int node, int father) {
    sz[node] = 1;
    for (auto it: graph[node])
        if (it != father) {
            dfs(it, node);
            sz[node] += sz[it];
        }
}

void solve(int node, int father, vector <int> &remainingPoints) {
    Point best(INF, INF);
    int who = -1;
    for (auto it: remainingPoints)
        if (points[it] < best) {
            best = points[it];
            who = it;
        }
    whichPct[node] = who;

    for (int i = 0; i < remainingPoints.size(); ++ i)
        if (remainingPoints[i] == who) {
            swap(remainingPoints[i], remainingPoints.back());
            remainingPoints.pop_back();
            break;
        }

    rf = points[whichPct[node]];
    sort(remainingPoints.begin(), remainingPoints.end(), cmp);

    vector <int> newPoints;
    int cursor = 0;
    for (auto it: graph[node])
        if (it != father) {
            newPoints.clear();
            int cnt = sz[it];
            while (cnt --)
                newPoints.push_back(remainingPoints[cursor ++]);

            solve(it, node, newPoints);
        }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    for (int i = 1; i < N; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= N; ++ i)
        cin >> points[i].x >> points[i].y;
    vector <int> v(N, 0);
    iota(v.begin(), v.end(), 1);


    dfs(1, 0);
    solve(1, 0, v);

    for (int i = 1; i <= N; ++ i)
        cout << whichPct[i] << " \n"[i == N];
    return 0;
}
