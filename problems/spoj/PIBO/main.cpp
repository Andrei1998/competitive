#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

const int MOD = 1111111111;

const int NMAX = 100 + 5;

class Matrix {
public:
    static int N;
    int mat[NMAX][NMAX];

    Matrix(int c = 0) {
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < N; ++ i)
            mat[i][i] = c;
    }

    friend Matrix operator*(const Matrix &a, const Matrix &b) {
        Matrix ans;
        for (int i = 0; i < N; ++ i)
            for (int k = 0; k < N; ++ k)
                for (int j = 0; j < N; ++ j)
                    ans.mat[i][j] = (ans.mat[i][j] + 1LL * a.mat[i][k] * b.mat[k][j]) % MOD;
        return ans;
    }

    Matrix operator^(int b) {
        Matrix ans(1);
        Matrix aux(*this);

        while (b) {
            if (b & 1)
                ans = ans * aux;
            aux = aux * aux;
            b >>= 1;
        }

        return ans;
    }
};

int Matrix :: N;

int c[NMAX];
int m2[NMAX];

int main()
{
    int N, D;
    cin >> N >> D;

    for (int i = 0; i <= D; ++i)
        cin >> c[i];

    Matrix :: N = D + 3;
    Matrix T;

    T.mat[0][1] = 1;
    T.mat[1][0] = 1;
    T.mat[1][1] = 1;

    for (int i = 0; i <= D; ++ i)
        T.mat[1][2 + i] = c[i];

    T.mat[2][2] = 1;

    for (int i = 3; i < D + 3; ++ i)
        for (int j = 1; j < D + 3; ++ j) {
            T.mat[i][j] = T.mat[i - 1][j];
            T.mat[i][j] = (T.mat[i][j] + 1LL * T.mat[i - 1][j - 1]) % MOD;
        }

    m2[0] = m2[1] = m2[2] = 1;
    for (int i = 1; i <= D; ++ i)
        m2[2 + i] = (m2[2 + i - 1] * 2LL) % MOD;

    T = T ^ N;

    int ans = 0;
    for (int i = 0; i <= D + 2; ++ i)
        ans = (ans + 1LL * m2[i] * T.mat[0][i]) % MOD;
    cout << ans << '\n';
    return 0;
}
