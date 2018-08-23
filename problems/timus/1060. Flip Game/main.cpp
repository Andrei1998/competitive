#include <iostream>
#include <queue>

using namespace std;

const int dx[] = {0, 0, 0, 1, -1};
const int dy[] = {0, 1, -1, 0, 0};

struct State {
    bool mat[4][4];

    State(int c = 0) {
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                mat[i][j] = c;
    }

    void do_move(int lin, int col) {
        for (int k = 0; k < 5; ++ k) {
            int nlin = lin + dx[k];
            int ncol = col + dy[k];

            if (nlin >= 0 && nlin < 4)
                if (ncol>= 0 && ncol < 4)
                    mat[nlin][ncol] ^= 1;
        }
    }

    inline int to_int() {
        int res = 0;
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j) {
                res <<= 1;
                res += mat[i][j];
            }
        return res;
    }
};

istream& operator>>(istream& f, State &s) {
    string str;
    for (int i = 0; i < 4; ++ i) {
        f >> str;
        for (int j = 0; j < 4; ++ j)
            s.mat[i][j] = (str[j] == 'b');
    }

    return f;
}

int dist[1 << 16];
queue <State> Q;

State goal;

int BFS() {
    for (int c = 0; c < 2; ++ c) {
        State full = State(c);
        dist[full.to_int()] = 1;
        Q.push(full);
    }

    State node;
    while (!Q.empty()) {
        node = Q.front();
        Q.pop();

        int old_dist = dist[node.to_int()];
        if (node.to_int() == goal.to_int())
            return old_dist;

        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j) {
                node.do_move(i, j);
                if (!dist[node.to_int()]) {
                    dist[node.to_int()] = 1 + old_dist;
                    Q.push(node);
                }
                node.do_move(i, j);
            }
    }

    return 0;
}

int main()
{
    cin >> goal;
    int ans = BFS() - 1;

    if (ans == -1)
        cout << "Impossible\n";
    else
        cout << ans << '\n';
    return 0;
}
