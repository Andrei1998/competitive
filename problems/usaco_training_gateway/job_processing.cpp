/*
ID: andreip3
LANG: C++14
TASK: job
*/
#include <bits/stdc++.h>

using namespace std;

void read(int &L, priority_queue <pair <int, int> > &pq) {
    for (int i = 1; i <= L; ++ i) {
        int x;
        cin >> x;
        pq.push({-x, x});
    }
}

vector <int> solve(int N, priority_queue <pair <int, int> > &pq) {
    vector <int> exits;
    while (N --) {
        pair <int, int> p = pq.top();
        pq.pop();
        exits.push_back(-p.first);
        p.first -= p.second;
        pq.push(p);
    }

    return exits;
}

priority_queue <pair <int, int> > pqA, pqB; // pair <release time from job if accepted, time to complete job>

int main() {
    freopen("job.in", "r", stdin);
    freopen("job.out", "w", stdout);

    // Reading
    int N, A, B;
    cin >> N >> A >> B;
    read(A, pqA);
    read(B, pqB);

    auto a = solve(N, pqA), b = solve(N, pqB);

    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater <int>());

    int ans = a[0] + b[0];
    for (int i = 0; i < a.size(); ++ i)
        ans = max(ans, a[i] + b[i]);

    cout << a.back() << ' ' << ans << '\n';
    return 0;
}
