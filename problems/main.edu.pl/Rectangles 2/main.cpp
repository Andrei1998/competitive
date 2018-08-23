#include <iostream>

#define lint long long int
using namespace std;

int main()
{
    int n;
    cin >> n;

    lint ans = 0;

    int j;
    for (int i = 1; i <= n; i = j + 1) {
        j = n / (n / i);
        ans += (n / i) * (j - i + 1LL);
    }

    //Add duplicates
    for (int i = 1; i * i <= n; ++ i)
        ++ ans;

    cout << ans / 2 << '\n';
    return 0;
}
