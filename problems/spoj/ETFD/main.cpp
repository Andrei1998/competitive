#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int K = 20;
const int N = 1000000;
const int NMAX = N + 5;

int phi[NMAX];
int depth[NMAX];

vector <int> freq[K];

int main()
{
    for (int i = 1; i <= N; ++ i) {
        phi[i] += i;
        for (int j = 2 * i; j <= N; j += i)
            phi[j] -= phi[i];
    }

    freq[0].push_back(1);
    for (int i = 2; i <= N; ++ i) {
        depth[i] = 1 + depth[phi[i]];
        if (depth[i] < 20)
            freq[depth[i]].push_back(i);
    }

    int T = 0;
    cin >> T;

    while (T --) {
        int l, r, k;
        cin >> l >> r >> k;

        int indR = upper_bound(freq[k].begin(), freq[k].end(), r) - freq[k].begin();
        int indL = lower_bound(freq[k].begin(), freq[k].end(), l) - freq[k].begin();

        cout << indR - indL << '\n';
    }

    return 0;
}
