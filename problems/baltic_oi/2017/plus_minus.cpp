#include <iostream>
#include <map>

using namespace std;

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

const int KMAX = 100000 + 5;

int N, M, K;
char sgn[KMAX];
int lin[KMAX];
int col[KMAX];

map <int, char> Map;

int cnt() {
    Map.clear();
    int free = N;
    for (int i = 1; i <= K; ++ i) {
        char sg = sgn[i];
        if (col[i] % 2 == 0)
            sg = '+' + '-' - sg;

        if (!Map.count(lin[i])) {
            Map[lin[i]] = sg;
            -- free;
        }
        else if (Map[lin[i]] != sg)
            return 0;
    }
    return raise(2, free);
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M >> K;

    int freq[2] = {0};
    for (int i = 1; i <= K; ++ i) {
        cin >> sgn[i] >> lin[i] >> col[i];

        bool sg = 0;
        if (sgn[i] == '+')
            sg = 1;
        ++ freq[(sg ^ lin[i] ^ col[i]) & 1];
    }

    int ans = cnt();

    swap(N, M);
    for (int i = 1; i <= K; ++ i)
        swap(lin[i], col[i]);
    ans = (ans + cnt()) % MOD;

    if (!freq[0] || !freq[1]) {
        if (!freq[0] && !freq[1])
            ans = (ans + MOD - 2) % MOD;
        else
            ans = (ans + MOD - 1) % MOD;
    }
    cout << ans << '\n';
    return 0;
}
