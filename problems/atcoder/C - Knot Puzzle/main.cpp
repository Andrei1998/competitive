#include <iostream>

using namespace std;

const int NMAX = 100000 + 5;

int N, L;
int v[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> L;

    for (int i = 1; i <= N; ++ i)
        cin >> v[i];

    int best = 0;
    int who = 0;
    for (int i = 1; i < N; ++ i)
        if (v[i] + v[i + 1] > best) {
            best = v[i] + v[i + 1];
            who = i;
        }

    if (best < L) {
        cout << "Impossible\n";
        return 0;
    }

    cout << "Possible\n";
    for (int i = 1; i < who; ++ i)
        cout << i << '\n';
    for (int i = N - 1; i > who; -- i)
        cout << i << '\n';
    cout << who << '\n';
    return 0;
}
