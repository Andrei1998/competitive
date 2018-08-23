#include <iostream>

using namespace std;

const int NMAX = 100000 + 5;

int N;
int A[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> A[i];

    int ans = 0;
    for (int i = 1; i <= N; ++ i) {
        ++ ans;
        bool jos = false;
        bool sus = false;

        int j;
        for (j = i + 1; j <= N; ++ j)
            if (A[j] != A[j - 1]) {
                if (A[j] < A[j - 1]) {
                    sus = true;
                    if (jos)
                        break;
                }
                else {
                    jos = true;
                    if (sus)
                        break;
                }
            }

        i = j - 1;
    }

    cout << ans << '\n';
    return 0;
}
