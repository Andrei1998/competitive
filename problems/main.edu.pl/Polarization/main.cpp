#include <iostream>
#include <vector>

#define lint long long int
using namespace std;

const int NMAX = 250000 + 5;

int n;
int sz[NMAX];

vector <int> graph[NMAX];
vector <int> centroids;

lint ans;

void dfsCentroid(int node, int father) {
    int largest = 0;
    sz[node] = 1;
    for (vector <int> :: iterator it = graph[node].begin(); it != graph[node].end(); ++ it)
        if (*it != father) {
            dfsCentroid(*it, node);
            sz[node] += sz[*it];

            if (sz[*it] > largest)
                largest = sz[*it];
        }

    if (n - sz[node] > largest)
        largest = n - sz[node];
    if (largest <= n / 2)
        centroids.push_back(node);
}

lint sumH;
void dfsKnapsack(int node, int father, int h) {
    sz[node] = 1;
    sumH += h;
    for (vector <int> :: iterator it = graph[node].begin(); it != graph[node].end(); ++ it)
        if (*it != father) {
            dfsKnapsack(*it, node, h + 1);
            sz[node] += sz[*it];
        }
}

int weights[NMAX];
int weightsSz;

int freq[NMAX];
bool dp[NMAX];

int aux[NMAX];

void addToDp(int val, int cnt) {
    for (int i = 0; i < n; ++ i)
        if (dp[i]) {
            ++ aux[i];
            if (i + val * (cnt + 1) < n)
                -- aux[i + val * (cnt + 1)];
        }

    for (int i = 0; i < n; ++ i) {
        if (i >= val)
            aux[i] += aux[i - val];
        dp[i] |= aux[i];
    }

    for (int i = 0; i < n; ++ i)
        aux[i] = 0;
}

void Knapsack() {
    for (int i = 1; i <= weightsSz; ++ i)
        ++ freq[weights[i]];

    dp[0] = 1;
    for (int i = 1; i < n; ++ i)
        dp[i] = 0;
    for (int i = 1; i < n; ++ i)
        if (freq[i])
            addToDp(i, freq[i]);

    for (int i = 0; i <= (n - 1) / 2; ++ i)
        if (dp[i])
            ans = max(ans, sumH + i * (n - 1LL - i));

    for (int i = 1; i <= weightsSz; ++ i)
        -- freq[weights[i]];
}

void solve(int root) {
    sumH = 0;
    dfsKnapsack(root, 0, 0);

    weightsSz = 0;
    for (vector <int> :: iterator it = graph[root].begin(); it != graph[root].end(); ++ it)
        weights[++ weightsSz] = sz[*it];
    Knapsack();
}

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i < n; ++ i) {
        int a, b;
        cin >> a >> b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfsCentroid(1, 0);

    for (vector <int> :: iterator root = centroids.begin(); root != centroids.end(); ++ root)
        solve(*root);

    cout << n - 1 << ' ' << ans << '\n';
    return 0;
}
