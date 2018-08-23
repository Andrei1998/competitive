#include <iostream>

using namespace std;

int main()
{
    int N, A, B;
    cin >> N >> A >> B;

    if (N == 1) {
        if (A != B)
            cout << "0\n";
        else
            cout << "1\n";
        return 0;
    }

    if (A > B) {
        cout << "0\n";
        return 0;
    }

    cout << 1LL * (N - 2) * (B - A) + 1 << '\n';
    return 0;
}
