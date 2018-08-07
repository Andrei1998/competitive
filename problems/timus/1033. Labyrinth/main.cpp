#include <iostream>
#include <string>

using namespace std;

const int NMAX = 40;

int N;
string mat[NMAX];

void fill(int lin, int col) {
    if (lin < 1 || col < 1 || lin > N || col > N || mat[lin][col] != '.')
        return ;
    mat[lin][col] = ' ';

    fill(lin - 1, col);
    fill(lin + 1, col);
    fill(lin, col - 1);
    fill(lin, col + 1);
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; ++ i) {
        cin >> mat[i];
        mat[i] = "*" + mat[i];
    }

    // Ohh...
    for (int i = 0; i <= N; ++ i)
        mat[0] += "*";

    fill(1, 1);
    fill(N, N);

    int ans = 0;
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= N; ++ j)
            if (mat[i][j] == ' ') {
                ans += ((mat[i - 1][j] != ' ') +
                        (mat[i + 1][j] != ' ') +
                        (mat[i][j - 1] != ' ') +
                        (mat[i][j + 1] != ' '));
            }

    ans -= 4;
    cout << 9 * ans << '\n';
    return 0;
}
