/*
ID: andreip3
LANG: C++14
TASK: camelot
*/
#include <bits/stdc++.h>

using namespace std;

bool readPos(pair <int, int> &k) {
    char _c;
    if (!(cin >> _c))
        return false;
    k.second = _c - 'A';
    if (!(cin >> k.first))
        return false;
    -- k.first;
    return true;
}

const int INF = 1E9 + 15;
int R, C;
static inline bool valid(const pair <int, int> &where) {
    return where.first >= 0 && where.second >= 0 && where.first < R && where.second < C;
}

vector <pair <int, int> > kingMoves, knightMoves;

static inline void doBFS(const pair <int, int> &start, vector <vector <int> > &dists, const vector <pair <int, int> > &moves) {
    dists[start.first][start.second] = 0;
    queue <pair <int, int> > q;
    q.push(start);
    while (!q.empty()) {
        const pair <int, int> node = q.front();
        q.pop();
        for (auto it: moves) {
            const pair <int, int> newNode = make_pair(node.first + it.first, node.second + it.second);
            if (valid(newNode) && dists[newNode.first][newNode.second] == INF) {
                dists[newNode.first][newNode.second] = dists[node.first][node.second] + 1;
                q.push(newNode);
            }
        }
    }
}

int main() {
    freopen("camelot.in", "r", stdin);
    freopen("camelot.out", "w", stdout);

    for (int i = -1; i <= 1; ++ i)
        for (int j = -1; j <= 1; ++ j)
            if (i || j)
                kingMoves.push_back(make_pair(i, j));
    for (int i = -2; i <= 2; ++ i)
        for (int j = -2; j <= 2; ++ j)
            if (abs(i) + abs(j) == 3)
                knightMoves.push_back(make_pair(i, j));

    cin >> R >> C;
    pair <int, int> king;
    readPos(king);

    vector <vector <int> > kingDists(R, vector <int>(C, INF));
    doBFS(king, kingDists, kingMoves);

    vector <pair <int, int> > knights;
    vector <vector <vector <int> > > knightDists;

    pair <int, int> knight;
    while (readPos(knight)) {
        knights.push_back(knight);
        knightDists.push_back(vector <vector <int> > (R, vector <int>(C, INF)));
        doBFS(knight, knightDists.back(), knightMoves);
    }

    int ans = INF;
    for (int i = 0; i < R; ++ i)
        for (int j = 0; j < C; ++ j) {
            vector <vector <int> > fromDest(R, vector <int>(C, INF));
            doBFS(make_pair(i, j), fromDest, knightMoves);

            // Meeting point (i, j)
            // No pickup
            long long int current = 0;
            for (const auto &k: knightDists)
                current += k[i][j];

            if (current >= ans)
                continue;

            current += kingDists[i][j];
            ans = min(current, 1LL * ans);

            // Pickup
            for (int k = 0; k < knights.size(); ++ k)
                for (int whereL = 0; whereL < R; ++ whereL)
                    for (int whereC = 0; whereC < C; ++ whereC) {
                        long long int aux = current - knightDists[k][i][j] - kingDists[i][j] + kingDists[whereL][whereC] + knightDists[k][whereL][whereC] + fromDest[whereL][whereC];
                        ans = min(aux, 1LL * ans);
                    }
        }
    cout << ans << '\n';
    return 0;
}
