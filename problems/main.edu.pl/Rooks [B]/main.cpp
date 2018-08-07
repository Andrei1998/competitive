#include <iostream>
#include <string>

using namespace std;

const int NMAX = 1000 + 5;

string mat[NMAX];
bool lin[NMAX];
bool col[NMAX];

int main() {
    ios_base :: sync_with_stdio(false);
    int N;
    cin >> N;

    for (int i = 1; i <= N; ++ i) {
        cin >> mat[i];
        for (int j = 1; j <= N; ++ j)
            if (mat[i][j - 1] == 'W') {
                lin[i] = true;
                col[j] = true;
            }
    }

    int i = 1, j = 1;
    while (i <= N && j <= N) {
        if (lin[i])
            ++ i;
        else if (col[j])
            ++ j;
        else {
            mat[i][j - 1] = 'W';
            ++ i, ++ j;
        }
    }

    for (int i = 1; i <= N; ++ i)
        cout << mat[i] << '\n';
    return 0;
}
