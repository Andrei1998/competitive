#include <iostream>

using namespace std;

int main()
{
    int X;
    cin >> X;

    int sum = 0;
    int days = 0;

    while (sum < X) {
        ++ days;
        sum += days;
    }

    cout << days << '\n';
    return 0;
}
