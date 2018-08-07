#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 1000 + 5;

int x[NMAX];
int y[NMAX];

int main()
{
    int N, M;
    cin >> N >> M; N --, M --;

    for (int i = 1; i <= N; ++ i)
        cin >> x[i];
    sort(x + 1, x + N + 1, greater <int>());
    for (int i = 1; i <= M; ++ i)
        cin >> y[i];
    sort(y + 1, y + M + 1, greater <int>());

    int ans = 0;

    int i = 1, j = 1;
    while (i <= N && j <= M)
        if (x[i] > y[j]) {
            ans += j * x[i];
            ++ i;
        }
        else {
            ans += i * y[j];
            ++ j;
        }

    while (i <= N) {
        ans += j * x[i];
        ++ i;
    }
    while (j <= M) {
        ans += i * y[j];
        ++ j;
    }

    cout << ans << '\n';
    return 0;
}
