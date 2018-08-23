#include <iostream>

using namespace std;

int brute(int a, int b) {
    int ans = 0;
    for (int i = a; i <= b; ++ i)
        ans ^= i;
    return ans;
}

int solve(int a, int b) {
    if (a != 0)
        return solve(0, a - 1) ^ solve(0, b);
    else if (b == 0)
        return 0;
    else if (!(b & 1))
        return b ^ solve(a, b - 1);
    else
        return ((b / 2) & 1) ^ 1;
}

bool failedTest() {
    for (int a = 0; a <= 100; ++ a)
        for (int b = a; b <= 100; ++ b)
            if (brute(a, b) != solve(a, b)) {
                cout << a << ' ' << b << endl;
                cout << brute(a, b) << ' ' << solve(a, b) << endl;
                return true;
            }
    return false;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    int T = 0;
    cin >> T;

    while (T --) {
        int a, b;
        cin >> a >> b;
        cout << solve(a, b) << '\n';
    }

    return 0;
}
