#include <iostream>

using namespace std;

int n;
char c[20];
int r[20];
int b[20];

bool erased[20];
int best;

void backtr(int left, int A, int B, int tA, int tB, int payed) {
    if (!left) {
        if (payed < best)
            best = payed;
        return ;
    }

    int optR = -1e9 - 15;
    int optR2 = 1e9 + 15;
    int whoR = -1;
    int optB = -1e9 - 15;
    int optB2 = 1e9 + 15;
    int whoB = -1;
    for (int i = 1; i <= n; ++ i)
        if (!erased[i]) {
            int cost = max(max(max(r[i] - A, 0) - tA, 0), max(max(b[i] - B, 0) - tB, 0));
            if (c[i] == 'R') {
                if (cost > optR) {
                    optR = cost;
                    optR2 = r[i];
                    whoR = i;
                }
                else if (cost == optR) {
                    if (r[i] < optR2) {
                        optR = cost;
                        optR2 = r[i];
                        whoR = i;
                    }
                }
            }
            else {
                if (cost > optB) {
                    optB = cost;
                    whoB = i;
                }
                else if (cost == optB) {
                    if (b[i] < optB2) {
                        optB = cost;
                        optB2 = b[i];
                        whoB = i;
                    }
                }
            }
        }

    if (whoR != -1) {
        erased[whoR] = true;
        backtr(left - 1, A + 1, B, tA + optR - max(r[whoR] - A, 0), tB + optR - max(b[whoR] - B, 0), payed + optR);
        erased[whoR] = false;
    }

    if (whoB != -1) {
        erased[whoB] = true;
        backtr(left - 1, A, B + 1, tA + optB - max(r[whoB] - A, 0), tB + optB - max(b[whoB] - B, 0), payed + optB);
        erased[whoB] = false;
    }
}

int main()
{
    cin >> n;

    for (int i = 1; i <= n; ++ i)
        cin >> c[i] >> r[i] >> b[i];

    best = 1e9 + 15;
    backtr(n, 0, 0, 0, 0, 0);

    best += n; //Moves cost, too
    cout << best << '\n';
    return 0;
}
