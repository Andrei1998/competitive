#include <iostream>
#include <cassert>

using namespace std;

int cr[205];
int ct[205];

int main()
{
    for (int i = 4; i <= 200; ++ i)
        cr[i] = cr[i - 1] + i;
    for (int i = 3; i <= 200; ++ i)
        ct[i] = ct[i - 1] + i;

    int d, r, t;
    cin >> d >> r >> t;

    for (int ageR = d; ageR <= 200; ++ ageR) {
        int crr = cr[ageR];
        int ctt = ct[ageR - d];

        int x = r - crr;
        if (x < 0)
            continue;

        if (ctt - x == t) {
            cout << x << '\n';
            return 0;
        }
    }

    assert(0);
    return 0;
}
