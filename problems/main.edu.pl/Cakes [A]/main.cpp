#include <iostream>
#include <vector>
#include <utility>
#include <set>

#define lint long long int
using namespace std;

const int NMAX = 100000 + 5;
const int MMAX = 250000 + 5;
const int MAGIC = 800;

int N, M;

vector <int> graph[NMAX];
pair <int, int> edges[MMAX];

set <pair <int, int> > Set;
bool big[NMAX];
int label[NMAX];
int labelsCount;

int cost[NMAX];

lint ans;
inline void addFromSmall(int a, int b, int c) {
    int cnt = big[a] + big[b] + big[c];
    if (cnt == 0)
        ans += 2 * max(cost[a], max(cost[b], cost[c]));
    else if (cnt == 1)
        ans += 3 * max(cost[a], max(cost[b], cost[c]));
    else
        ans += 6 * max(cost[a], max(cost[b], cost[c]));
}

inline void addFromBig(int a, int b, int c) {
    ans += max(cost[a], max(cost[b], cost[c]));
}

bool adj[MMAX / MAGIC + 5][MMAX / MAGIC + 5];

vector <int> bigGraph[MMAX / MAGIC + 5];

int whichNode[MMAX / MAGIC + 5];

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 1; i <= N; ++ i)
        cin >> cost[i];

    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;

    ans /= 2;
        edges[i].first = a;
        edges[i].second = b;
        graph[a].push_back(b);
        graph[b].push_back(a);

        Set.insert(make_pair(a, b));
        Set.insert(make_pair(b, a));
    }

    for (int i = 1; i <= N; ++ i)
        if (graph[i].size() > MAGIC) {
            big[i] = true;
            label[i] = ++ labelsCount;
            whichNode[labelsCount] = i;
        }

    //Count from smalls
    for (int i = 1; i <= N; ++ i)
        if (!big[i])
            for (int j = 0; j < graph[i].size(); ++ j)
                for (int k = j + 1; k < graph[i].size(); ++ k)
                    if (Set.count(make_pair(graph[i][j], graph[i][k])))
                        addFromSmall(i, graph[i][j], graph[i][k]);
    ans /= 2;

    //Count from bigs
    for (int i = 1; i <= N; ++ i)
        if (big[i])
            for (int j = 0; j < graph[i].size(); ++ j)
                if (big[graph[i][j]]) {
                    adj[label[i]][label[graph[i][j]]] = true;
                    bigGraph[label[i]].push_back(label[graph[i][j]]);
                }

    for (int i = 1; i <= labelsCount; ++ i)
        for (int j = 0; j < bigGraph[i].size(); ++ j)
            for (int k = j + 1; k < bigGraph[i].size(); ++ k)
                if (adj[bigGraph[i][j]][bigGraph[i][k]])
                    addFromBig(whichNode[i], whichNode[bigGraph[i][j]], whichNode[bigGraph[i][k]]);

    //Print
    cout << ans / 3 << '\n';
    return 0;
}
