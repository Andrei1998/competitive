#include <iostream>

using namespace std;

int main()
{
    ios_base :: sync_with_stdio(false);
    //cin.tie(0);

    int N;
    cin >> N;

    int odds = 0, evens = 0;
    for (int i = 1; i <= N; ++ i) {
        int val;
        cin >> val;

        if (val & 1)
            ++ odds;
        else
            ++ evens;
    }

    evens += (odds / 2);
    odds %= 2;

    while (evens > 1)
        evens --;

    if (odds + evens == 1)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}
