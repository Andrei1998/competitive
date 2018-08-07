#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 200000 + 5;

int N, T;
int v[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> T;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];
    sort(v + 1, v + N + 1);

    int ans = 0;
    for (int i = 1; i <= N; ++ i)
        if (i == 1 || v[i - 1] + T <= v[i])
            ans += T;
        else
            ans += v[i] + T - (v[i - 1] + T);

    cout << ans << '\n';
    return 0;
}
