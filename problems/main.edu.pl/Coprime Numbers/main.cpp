#include <iostream>

#define lint long long int
using namespace std;

const int NMAX = 1e6 + 5;
const int VALMAX = 3 * NMAX;

int freq[VALMAX];

int divs[VALMAX];
int mob[VALMAX];

int main()
{
    ios_base :: sync_with_stdio(false);
    int N;
    cin >> N;

    for (int i = 1; i <= N; ++ i) {
        int val;
        cin >> val;
        ++ freq[val];
    }

    //Mobius function
    for (int i = 1; i < VALMAX; ++ i)
        mob[i] = 1;
    for (int i = 2; i < VALMAX; ++ i)
        if (!divs[i]) {
            for (int j = i; j < VALMAX; j += i)
                ++ divs[j], mob[j] *= (-1);
            if (i <= (VALMAX - 1) / i)
                for (int j = i * i; j < VALMAX; j += i * i)
                    mob[j] = 0;
        }

    //Answer
    lint ans = 0;
    for (int i = 1; i < VALMAX; ++ i)
        if (mob[i]) {
            for (int j = 2 * i; j < VALMAX; j += i)
                freq[i] += freq[j];
            ans += mob[i] * freq[i] * (freq[i] - 1LL) / 2;
        }

    cout << ans << '\n';
    return 0;
}
