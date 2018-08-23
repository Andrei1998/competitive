#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 100 + 5;
const int MMAX = 9900 + 5;
const int KMAX = 1000 + 5;
const int INF = 1E9 + 15;
const double EPS = 1E-10;

int N, M, K;

int B[NMAX][KMAX];
int S[NMAX][KMAX];

int len[NMAX][NMAX];
int obj[NMAX][NMAX];
long double dist[NMAX][NMAX];

void rf() {
    for (int k = 1; k <= N; ++ k)
        for (int i = 1; i <= N; ++ i)
            for (int j = 1; j <= N; ++ j)
                if (len[i][k] < INF && len[k][j] < INF && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

bool works(long double edgeCost) {
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= N; ++ j)
            dist[i][j] = len[i][j] * edgeCost - obj[i][j];

    rf();
    for (int i = 1; i <= N; ++ i)
        if (dist[i][i] < 0)
            return true;
    return false;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= K; ++ j)
            cin >> B[i][j] >> S[i][j];

    for (int i = 1; i <= N; ++ i)
        for (int j = i + 1; j <= N; ++ j)
            len[i][j] = len[j][i] = INF;

    for (int i = 1; i <= M; ++ i) {
        int a, b, c;
        cin >> a >> b >> c;
        len[a][b] = c;
    }

    // Cost over distances
    for (int k = 1; k <= N; ++ k)
        for (int i = 1; i <= N; ++ i)
            for (int j = 1; j <= N; ++ j)
                if (len[i][k] + len[k][j] < len[i][j])
                    len[i][j] = len[i][k] + len[k][j];

    // Cost over objects
    for (int i = 1; i <= N; ++ i)
        for (int k = 1; k <= K; ++ k)
            if (B[i][k] != -1)
                for (int j = 1; j <= N; ++ j)
                    if (S[j][k] != -1 && B[i][k] < S[j][k])
                        obj[i][j] = max(obj[i][j], S[j][k] - B[i][k]);

    long double st = 0, dr = INF;
    for (int i = 0; i < 70; ++ i) {
        long double mid = (st + dr) * 0.5L;
        if (works(mid))
            st = mid;
        else
            dr = mid;
    }

    cout << (int)(st + EPS) << '\n';
    return 0;
}
