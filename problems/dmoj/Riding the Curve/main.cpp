#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

int main()
{
    int M, K, N;
    cin >> M >> K >> N;

    for (int x = 0; x <= M; ++ x)
        if ((x + K) * 1000LL >= 595LL * N) {
            cout << x << '\n';
            return 0;
        }

    cout << "have mercy snew\n";
    return 0;
}
