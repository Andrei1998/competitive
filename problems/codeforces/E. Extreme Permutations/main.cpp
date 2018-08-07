#include <bits/stdc++.h>

using namespace std;

const int NMAX = 27 + 5;

int N;
int fxd[NMAX];
bool isFixed[NMAX];

int p[NMAX];
void backtr(int nr, int remBig, int remSmall) {

    if (remSmall * 2 > nr)
        return ;
    if (remSmall * 2 <= (N + 1) / 2)
        return ;

    /*for (int i = 1; i <= N; ++ i)
        cout << p[i] << ' ';
    cout << endl;*/

    for (int i = 1; i <= N; ++ i)
        if ((i & 1) && !p[i] && ((isFixed[nr] && fxd[i] == nr) || (!isFixed[nr] && !fxd[i]))) {
            int newRemSmall = remSmall;
            if (i - 2 >= 1 && p[i - 2]) {
                if (2 * newRemSmall <= nr)
                    newRemSmall --;
                else
                    continue;
            }

            if (i + 2 <= N && p[i + 2]) {
                if (2 * newRemSmall <= nr)
                    newRemSmall --;
                else
                    continue;
            }

            p[i] = nr;
            backtr(nr - 1, remBig - 1, newRemSmall);
            p[i] = 0;
        }
}

int main() {
    //cin >> N;
    N = 27;
    for (int i = 1; i <= N; ++ i) {
        //cin >> fxd[i];
        //isFixed[fxd[i]] = true;
    }

    backtr(N, (N + 1) / 2, N / 2);
    return 0;
}
