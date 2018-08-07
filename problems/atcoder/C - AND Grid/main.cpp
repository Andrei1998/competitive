#include <iostream>
#include <string>

using namespace std;

const int NMAX = 500 + 5;

int N, M;
string red[NMAX];
string blue[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;

    for (int i = 0; i < N; ++ i) {
        cin >> red[i];
        blue[i] = red[i];
    }

    for (int j = 0; j < M; ++ j)
        for (int i = 0; i < N; ++ i)
            if (j & 1)
                red[i][j] = '#';
            else
                blue[i][j] = '#';
    for (int i = 0; i < M; ++ i) {
        red[0][i] = blue[N - 1][i] = '#';
        blue[0][i] = red[N - 1][i] = '.';
    }

    for (int i = 0; i < N; ++ i)
        cout << red[i] << '\n';
    cout << '\n';
    for (int i = 0; i < N; ++ i)
        cout << blue[i] << '\n';
    return 0;
}
