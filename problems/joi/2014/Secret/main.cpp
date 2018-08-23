#include <bits/stdc++.h>
//#include "secret.h"

using namespace std;

void Init(int N, int A[]);
int Query(int L, int R);

int Secret(int X, int Y) {
    //static int cnt = 0; ++ cnt;
    //cout << cnt << endl;
    return X ^ Y;
}

int Brute(int A[], int L, int R) {
    int ans = A[L];
    for (int i = L + 1; i <= R; ++ i)
        ans = Secret(ans, A[i]);
    return ans;
}

int main()
{
    int N = 1000;
    int *A = new int[N];
    for (int i = 0; i < N; ++ i)
        A[i] = rand() % 1000;
    Init(N, A);
    for (int i = 0; i < N; ++ i)
        for (int j = i; j < N; ++ j)
            if (Query(i, j) != Brute(A, i, j))
                return 1;
    return 0;
}

const int NMAX = 1000 + 5;
int N, A[NMAX];
int ans[11][NMAX];

void init(int level, int st, int dr) {
    if (st > dr)
        return ;

    int mid = (st + dr) >> 1;

    ans[level][mid] = A[mid];
    for (int i = mid - 1; i >= st; -- i)
        ans[level][i] = Secret(A[i], ans[level][i + 1]);

    ans[level][mid + 1] = A[mid + 1];
    for (int i = mid + 2; i <= dr; ++ i)
        ans[level][i] = Secret(ans[level][i - 1], A[i]);

    if (st != dr) {
        init(level + 1, st, mid);
        init(level + 1, mid + 1, dr);
    }
}

void Init(int _N, int _A[]) {
    N = _N;
    for (int i = 1; i <= N; ++ i)
        A[i] = _A[i - 1];
    init(0, 1, N);
}

int query(int level, int st, int dr, int L, int R) {
    if (st == dr)
        return A[st];

    int mid = (st + dr) >> 1;
    if (L <= mid && R > mid)
        return Secret(ans[level][L], ans[level][R]);
    else if (R <= mid)
        return query(level + 1, st, mid, L, R);
    else
        return query(level + 1, mid + 1, dr, L, R);
}

int Query(int L, int R) {
    return query(0, 1, N, L + 1, R + 1);
}
