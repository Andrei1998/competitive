#include <iostream>

using namespace std;

int main()
{
    int T = 0;
    cin >> T;

    while (T --) {
        int x, y;
        cin >> x >> y;

        if (x == y) {
            if (x % 2 == 0)
                cout << 2 * x << '\n';
            else
                cout << 2 * (x - 1) + 1 << '\n';
        }
        else if (y + 2 == x) {
            if (x % 2 == 0)
                cout << 2 * x - 2 << '\n';
            else
                cout << 2 * (x - 1) - 2 + 1 << '\n';
        }
        else
            cout << "No Number\n";
    }
    return 0;
}
