#include <iostream>

using namespace std;

long long int solve(int a, int b) {
    return (a + b + 1LL) * (a + b) / 2 + a + 1;
}

int main()
{
    int T = 0;
    cin >> T;
    while (T --) {
        int a, b;
        cin >> a >> b;
        cout << solve(a, b) << '\n';
    }
    return 0;
}
