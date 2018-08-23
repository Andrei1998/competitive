#include <iostream>
#include <algorithm>
#include <cstdio>
#include <stack>

using namespace std;

const int NMAX = 100000 + 5;
typedef long long int lint;

int N;
int v[NMAX];
lint sPart[NMAX];

int st[NMAX];
int dr[NMAX];

bool win[NMAX];

bool vis[NMAX];
void solve(int node) {
    if (vis[node])
        return ;
    vis[node] = true;

    if (st[node] == 0 && dr[node] == N + 1)
        win[node] = true;
    else {
        lint sum = sPart[dr[node] - 1] - sPart[st[node]];
        if (v[st[node]] <= 2 * sum) {
            solve(st[node]);
            win[node] |= win[st[node]];
        }
        if (v[dr[node]] <= 2 * sum) {
            solve(dr[node]);
            win[node] |= win[dr[node]];
        }
    }
}

int main()
{
    //freopen("data.in", "r", stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];
    v[0] = v[N + 1] = 2E9 + 5;

    sort(v + 1, v + N + 1);
    for (int i = 1; i <= N; ++ i)
        sPart[i] = sPart[i - 1] + v[i];

    stack <int> stk;
    stk.push(0);

    for (int i = 1; i <= N; ++ i) {
        while (v[stk.top()] <= v[i])
            stk.pop();
        st[i] = stk.top();
        stk.push(i);
    }

    while (!stk.empty())
        stk.pop();
    stk.push(N + 1);

    for (int i = N; i; -- i) {
        while (v[stk.top()] <= v[i])
            stk.pop();
        dr[i] = stk.top();
        stk.push(i);
    }

    int ans = 0;
    for (int i = 1; i <= N; ++ i) {
        solve(i);
        ans += win[i];
    }

    cout << ans << '\n';
    return 0;
}
