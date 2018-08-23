#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 100000 + 5;

int N;
int v[NMAX];

int main()
{
    int C, K;
    cin >> N >> C >> K;

    for (int i = 1; i <= N; ++ i)
        cin >> v[i];
    sort(v + 1, v + N + 1);

    int cnt = 0;

    int rem = 0;
    int limit = -1;
    for (int i = 1; i <= N; ++ i) {
        if (!rem || v[i] > limit) {
            ++ cnt;
            rem = C;
            limit = v[i] + K;
        }
        -- rem;
    }

    cout << cnt << '\n';
    return 0;
}
