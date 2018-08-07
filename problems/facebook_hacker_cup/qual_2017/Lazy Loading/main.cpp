#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 100 + 5;

int N;
int w[NMAX];

int test() {
    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> w[i];

    sort(w + 1, w + N + 1, greater <int>());

    int ans = 0;
    for (int i = 1; i <= N; ++ i) {
        int sum = w[i];

        while (i < N && sum < 50)
            sum += w[i], N --;

        if (sum < 50)
            break;
        else
            ++ ans;
    }

    return ans;
}

int main()
{
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);

    int T = 0;
    cin >> T;

    for (int i = 1; i <= T; ++ i)
        cout << "Case #" << i << ": " << test() << '\n';
    return 0;
}
