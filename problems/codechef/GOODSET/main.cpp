#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T --) {
        int N;
        cin >> N;
        for (int i = N; i; -- i)
            cout << 500 - i << " \n"[i == 1];
    }
    return 0;
}
