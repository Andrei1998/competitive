#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#define lint long long int
using namespace std;

const int NMAX = 5005;
const int MOD = 1000000000 + 7;

int n;
vector <pair <int, int> > graph[NMAX];

lint sum;
bool marked[NMAX];

void dfs(int node, int father, lint current) {
    sum += current;
    for (auto it: graph[node])
        if (it.first != father && !marked[it.first])
            dfs(it.first, node, current + it.second);
}

lint final_ans;
void backtr(int ram, lint current) {
    if (!ram) {
        final_ans += current;
        if (final_ans >= MOD)
            final_ans -= MOD;

        return ;
    }

    for (int i = 1; i <= n; ++ i)
        if (!marked[i]) {
            marked[i] = true;
            sum = 0;
            dfs(i, 0, 0);
            lint val = sum;

            current += val;
            backtr(ram - 1, current);
            current -= val;
            marked[i] = false;
        }
}

int main() {
    cin >> n;

    for (int i = 1; i < n; ++ i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back(make_pair(b, c));
        graph[b].push_back(make_pair(a, c));
    }

    backtr(n, 0);

    cout << final_ans% MOD << '\n';
    return 0;
}
