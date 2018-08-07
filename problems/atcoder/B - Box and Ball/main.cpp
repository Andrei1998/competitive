#include <iostream>

using namespace std;

const int NMAX = 100000 + 5;

int cnt[NMAX];
bool red[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; ++ i)
        cnt[i] = 1;
    red[1] = true;

    while (M --) {
        int a, b;
        cin >> a >> b;

        if (red[a]) {
            if (cnt[a] == 1) {
                red[a] = false;
                red[b] |= true;
            }
            else
                red[b] |= true;
        }

        ++ cnt[b];
        -- cnt[a];
    }

    int ans = 0;
    for (int i = 1; i <= N; ++ i)
        ans += red[i];
    cout << ans << '\n';
    return 0;
}
