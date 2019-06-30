#include <bits/stdc++.h>

using namespace std;

template <typename T>
class G {
  public:
    typedef vector <T> Row;
    typedef vector <Row> Matrix;
    static constexpr T EPS = static_cast <T>(1E-10);
    
    G() {}
    G(const int N, const int M): mat(Row(M + 1), N) {}
    G(const Matrix &m): mat(m) {}

    Row& operator[](const int index) { return mat[index]; }
    void push_back(const Row &r) { mat.push_back(r); }

    Row solve() {
        const int N = mat.size();
        const int M = mat[0].size();
        vector <T> ans(M - 1, static_cast <T>(0.0)); 
        vector <int> where(M - 1, -1);
        int l = 0;
        for (int c = 0; c < M - 1; ++c) {
            pair <T, int> maximum(-1, -1);
            for (int i = l; i < N; ++i) {
                maximum = max(maximum, make_pair(abs(mat[i][c]), i));
            }
            if (maximum.first < EPS) {
                continue;
            }
            where[c] = l;
            swap(mat[l], mat[maximum.second]);
            const T alpha = mat[l][c];
            for (int j = c; j < M; ++j) {
                mat[l][j] /= alpha;
            }
            // mat[l][c] = 1
            for (int i = 0; i < N; ++i) {
                if (i == l) {
                    continue;
                }
                const T beta = mat[i][c];
                for (int j = c; j < M; ++j) {
                    mat[i][j] -= mat[l][j] * beta;       
                }
            }
            ++l;
        }
        for (int i = l; i < N; ++i) {
            if (fabs(mat[i][M - 1]) >= EPS) {
                throw logic_error("Impossible");
            }
        }
        for (int c = 0; c < M - 1; ++c) {
            if (where[c] != -1) {
                ans[c] = mat[where[c]][M - 1];
            }
        }
        return ans;
    }
    
  private:
    Matrix mat;
};

typedef G <double> Gauss;

int main() {
    int N, M;
    cin >> N >> M;
    Gauss g;
    vector <double> d(M + 1);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= M; ++j) {
            cin >> d[j];
        }
        g.push_back(d); // Push back a new equation
    }
    vector <double> sol;
    try {
        sol = g.solve(); // Get solution
        cout << fixed << setprecision(8);
        for (int i = 0; i < M; ++i) {
            cout << sol[i] << " \n"[i + 1 == M];
        }
    } catch (const logic_error&) {
        cout << "Impossible\n";
    }
    return 0;    
}