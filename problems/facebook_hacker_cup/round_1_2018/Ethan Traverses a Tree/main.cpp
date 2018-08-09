#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2000 + 5;
int N, K;
int A[NMAX], B[NMAX];

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);

    int T = 0;
    cin >> T;
    for (int t = 1; t <= T; ++ t) {
        cin >> N >> K;
        for (int i = 1; i <= N; ++ i)
            cin >> A[i] >> B[i];

        vector <int> pre, wherePre(N + 1);
        function <void(int)> getPre = [&pre, &wherePre, &getPre](int node) {
            if (node == 0)
                return ;
            pre.push_back(node), wherePre[node] = pre.size() - 1;
            getPre(A[node]), getPre(B[node]);
        };
        vector <int> post;
        function <void(int)> getPost = [&post, &getPost](int node) {
            if (node == 0)
                return ;
            getPost(A[node]), getPost(B[node]);
            post.push_back(node);
        };

        getPre(1), getPost(1);

        vector <bool> vis(N + 1);
        vector <int> color(N + 1);

        int colors = 0;
        for (int i = 0; i < N; ++ i) {
            int val = pre[i];
            if (!vis[val]) {
                if (colors < K)
                    ++ colors;
                while (!vis[val]) {
                    vis[val] = true;
                    color[val] = colors;
                    val = post[wherePre[val]];
                }
            }
        }

        if (colors < K)
            cout << "Case #" << t << ": Impossible\n";
        else {
            cout << "Case #" << t << ": ";
            for (int i = 1; i <= N; ++ i)
                cout << color[i] << " \n"[i == N];
        }
    }
    return 0;
}
