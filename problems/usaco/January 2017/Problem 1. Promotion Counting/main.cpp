#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

//14 min
const int NMAX = 100000 + 5;

int N;
int v[NMAX];

vector <pair <int, int> > sorted;

vector <int> graph[NMAX];

int first[NMAX];
int last[NMAX];
int pos;

void dfs(int node) {
    first[node] = ++ pos;
    for (auto it: graph[node])
        dfs(it);
    last[node] = pos;
}

#define lsb(x) ((x) & (-(x)))
int aib[NMAX];

void update(int where) {
    for (; where <= N; where += lsb(where))
        ++ aib[where];
}

int query(int where) {
    int ans = 0;
    for (; where; where -= lsb(where))
        ans += aib[where];
    return ans;
}

int ans[NMAX];

int main()
{
    //ios_base :: sync_with_stdio(false);
    ifstream cin("promote.in");
    ofstream cout("promote.out");

    cin >> N;
    for (int i = 1; i <= N; ++ i) {
        cin >> v[i];
        sorted.push_back(make_pair(v[i], i));
    }
    sort(sorted.begin(), sorted.end(), greater <pair <int, int> >());

    for (int i = 2; i <= N; ++ i) {
        int father;
        cin >> father;
        graph[father].push_back(i);
    }

    dfs(1);

    for (int i = 0; i < N; ++ i) {
        int node = sorted[i].second;
        ans[node] = query(last[node]) - query(first[node] - 1);
        update(first[node]);
    }

    for (int i = 1; i <= N; ++ i)
        cout << ans[i] << '\n';
    return 0;
}
