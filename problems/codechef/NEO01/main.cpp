#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 100000 + 5;
typedef long long int lint;

int N;
lint sPart[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int T = 0;
    cin >> T;
    while (T --) {
        cin >> N;
        for (int i = 1; i <= N; ++ i)
            cin >> sPart[i];
        sort(sPart + 1, sPart + N + 1);
        for (int i = 1; i <= N; ++ i)
            sPart[i] += sPart[i - 1];
        lint best = -(4E18 + 15);

        for (int i = 0; i <= N; ++ i) {
            lint aux = sPart[i] + 1LL * (sPart[N] - sPart[i]) * (N - i);
            best = max(best, aux);
        }
        cout << best << '\n';
    }
    return 0;
}
