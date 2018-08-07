#include <iostream>

using namespace std;

int main()
{
    int n, d;
    cin >> n >> d;

    if (d == 0) {
        cout << "BRAK\n";
        return 0;
    }
    else if (d == 1) {
        if (n == 2)
            cout << "1 2\n";
        else
            cout << "BRAK\n";
        return 0;
    }

    for (int i = 1; i <= d; ++ i)
        cout << i << ' ' << i + 1 << '\n';
    for (int i = d + 2; i <= n; ++ i)
        cout << i << ' ' << d << '\n';
    return 0;
}
