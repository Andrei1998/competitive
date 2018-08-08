#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int lint;

unordered_map <lint, int> Map;
string str;
const int MAGIC = 8;
const int NMAX = 75000 + 5;

void add(lint &hs, int val) {
    hs *= 123LL;
    hs += val;
}

lint ans;
void loadAll() {
    lint aux;
    for (int i = 0; i < str.size(); ++ i) {
        aux = 0;
        for (int j = 0; j < MAGIC && i + j < str.size(); ++ j) {
            add(aux, str[i + j]);
            ++ Map[aux];
            if (Map[aux] == 1)
                ++ ans;
        }
    }
}

void unload(const int pos) {
    lint aux;
    for (int i = pos - (MAGIC - 1); i <= pos; ++ i) {
        aux = 0;
        for (int j = 0; j < MAGIC && i + j < str.size(); ++ j) {
            add(aux, str[i + j]);
            if (i + j >= pos) {
                -- Map[aux];
                if (Map[aux] == 0)
                    Map.erase(aux), -- ans;
            }
        }
    }
}

void reload(const int pos) {
    lint aux;
    for (int i = pos - (MAGIC - 1); i <= pos; ++ i) {
        aux = 0;
        for (int j = 0; j < MAGIC && i + j < str.size(); ++ j) {
            add(aux, str[i + j]);
            if (i + j >= pos) {
                ++ Map[aux];
                if (Map[aux] == 1)
                    ++ ans;
            }
        }
    }
}

int main() {
    //freopen("data.in", "r", stdin);
    //freopen("data.out", "w", stdout);

    int v[20];
    for (int i = 1; i <= 10; ++ i)
        cin >> v[i];

    int sum = 0;
    for_each(v + 1, v + N + 1, [](int x) {
        sum += x;
    });

    Map.max_load_factor(0.5);
    Map.reserve(10 * NMAX);

    int N, Q;
    cin >> N >> Q;
    cin >> str;

    loadAll();
    for (int i = MAGIC + 1; i <= N; ++ i)
        ans += N - i + 1;

    while (Q --) {
        int P;
        char C;
        cin >> P >> C; -- P;

        unload(P), str[P] = C, reload(P);
        cout << ans << '\n';
    }

    return 0;
}
