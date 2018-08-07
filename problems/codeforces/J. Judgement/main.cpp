#include <iostream>
#include <bitset>
#include <cstdlib>

using namespace std;

const int NMAX = 100;
const int VALMAX = 1000000 + 5;

int maximum[VALMAX];
bitset <NMAX> sol[VALMAX];

int N, P, Q;
int a[NMAX];
int b[NMAX];

void fail() {
    for (int i = 0; i < Q; ++ i) {
        maximum[i] = 0;
        sol[i] = 0;
    }

    for (int t = 0; t < N; ++ t) {
        for (int i = Q - 1; i >= b[t]; -- i) {
            int val = maximum[i - b[t]] + a[t];
            if (val > maximum[i]) {
                maximum[i] = val;
                sol[i] = sol[i - b[t]];
                sol[i].set(t);

                if (val >= P) {
                    cout << "NO\n";
                    for (int j = 0; j < N; ++ j)
                        cout << sol[i][j];
                    cout << '\n';
                    exit(0);
                }
            }
        }
    }
}

int main()
{
    cin >> N;
    cin >> P;
    for (int i = 0; i < N; ++ i)
        cin >> a[i];
    cin >> Q;
    for (int i = 0; i < N; ++ i)
        cin >> b[i];

    /*N = 100;
    for (int i = 0; i < N; ++ i)
        a[i] = b[i] = 1;
    P = Q = 1000000;*/

    fail();
    for (int i = 0; i < N; ++ i)
        swap(a[i], b[i]);
    swap(P, Q);
    fail();

    cout << "YES\n";
    return 0;
}
