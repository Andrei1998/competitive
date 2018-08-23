#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NMAX = 100 + 5;
const int MOD = 1000000000 + 7;

int raise(int a, int b) {
    if (!b)
        return 1;
    else if (b & 1)
        return (1LL * a * raise(a, b - 1)) % MOD;
    else {
        int aux = raise(a, b >> 1);
        return (1LL * aux * aux) % MOD;
    }
}

int inv(int nr) {
    return raise(nr, MOD - 2);
}

int N;
int mat[NMAX][NMAX];

inline void mult(int lin, int alpha) {
    for (int i = 1; i <= N; ++ i)
        mat[lin][i] = (1LL * mat[lin][i] * alpha) % MOD;
}

inline void subtract(int start, int lin1, int alpha, int lin2) {
    for (int i = start; i <= N; ++ i) {
        mat[lin1][i] = (mat[lin1][i] - 1LL * alpha * mat[lin2][i]) % MOD;
        if (mat[lin1][i] < 0)
            mat[lin1][i] += MOD;
    }
}

inline void _swap(int lin1, int lin2) {
    for (int i = 1; i <= N; ++ i)
        swap(mat[lin1][i], mat[lin2][i]);
}

bool det() {
    for (int col = 1; col <= N; ++ col) {
        int pivot = -1;
        for (int lin = col; lin <= N; ++ lin)
            if (mat[lin][col]) {
                pivot = lin;
                break;
            }

        if (pivot == -1)
            return false;
        _swap(col, pivot);
        mult(col, inv(mat[col][col]));

        for (int lin = col + 1; lin <= N; ++ lin)
            if (mat[lin][col])
                subtract(col, lin, mat[lin][col], col);
    }

    return true;
}

void test() {
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= N; ++ j)
            mat[i][j] = 0;

    int M = 0;
    cin >> N >> M;

    while (M --) {
        int a, b;
        cin >> a >> b;

        if (a > b)
            swap(a, b);

        ++ mat[a][b];
        -- mat[b][a];
        if (mat[b][a] < 0)
            mat[b][a] += MOD;
    }

    for (int i = 1; i <= N; ++ i)
        for (int j = i + 1; j <= N; ++ j) {
            int aux = rand() % (MOD - 1) + 1;
            mat[i][j] = (1LL * mat[i][j] * aux) % MOD;
            mat[j][i] = (1LL * mat[j][i] * aux) % MOD;
        }

    if (det())
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main()
{
    srand(time(NULL));

    int T = 0;
    cin >> T;

    while (T --)
        test();
    return 0;
}
