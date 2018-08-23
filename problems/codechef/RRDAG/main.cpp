#include <iostream>
#include <string>

using namespace std;

const int NMAX = 1500 + 5;
string mat[NMAX];

int N;
int ord[NMAX];
int cnt;

bool vis[NMAX];
void dfs(int node) {
    vis[node] = true;
    for (int i = 0; i < N; ++ i)
        if (mat[node][i] == '1' && !vis[i])
            dfs(i);
    ord[cnt --] = node;
}

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> N;

    for (int i = 0; i < N; ++ i)
        cin >> mat[i];

    cnt = N - 1;
    for (int i = 0; i < N; ++ i)
        if (!vis[i])
            dfs(i);

    for (int i = 0; i < N; ++ i)

    return 0;
}
