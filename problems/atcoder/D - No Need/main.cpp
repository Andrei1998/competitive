#include <iostream>
#include <bitset>

using namespace std;

const int NMAX = 5000 + 5;
bitset <NMAX> leftDp[NMAX];
bitset <NMAX> rightDp[NMAX];

int N, K;
int v[NMAX];

int main()
{
    cin >> N >> K;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];

    leftDp[0].set(0, 1);
    for (int i = 1; i <= N; ++ i)
        leftDp[i] = leftDp[i - 1] | (leftDp[i - 1] << v[i]);

    rightDp[N + 1].set(0, 1);
    for (int i = N; i; -- i)
        rightDp[i] = rightDp[i + 1] | (rightDp[i + 1] << v[i]);

    int ans = 0;
    for (int i = 1; i <= N; ++ i) {
        ;
    }

    cout << ans << '\n';
    return 0;
}
