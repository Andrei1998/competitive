#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 100000 + 5;
int A[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);

    int N, L, T;
    cin >> N >> L >> T;

    long long int tr = 0;
    for (int i = 1; i <= N; ++ i) {
        cin >> A[i];
        int w;
        cin >> w;

        if (w == 1) {
            tr += (A[i] + T) / L;
            A[i] += T;
            A[i] %= L;
        }
        else {
            if (T > A[i]) {
                int t = T - A[i] - 1;
                tr -= t / L + 1;
            }

            A[i] = (A[i] - T) % L;
            if (A[i] < 0)
                A[i] += L;
        }
    }

    sort(A + 1, A + N + 1);

    tr %= N;
    if (tr < 0)
        tr += N;

    rotate(A + 1, A + tr + 1, A + N + 1);
    for (int i = 1; i <= N; ++ i)
        cout << A[i] << '\n';
    return 0;
}
