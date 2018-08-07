#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 50 + 5;

int N, R;
int x[NMAX];
int y[NMAX];

ifstream cin("data.in");
int test() {
    cin >> N >> R;
    for (int i = 1; i <= N; ++ i)
        cin >> x[i] >> y[i];

    int ans = 1;
    for (int x1 = 1; x1 <= N; ++ x1)
        for (int y1 = 1; y1 <= N; ++ y1)
            for (int x2 = 1; x2 <= N; ++ x2)
                for (int y2 = 1; y2 <= N; ++ y2) {
                    int cnt = 0;
                    for (int i = 1; i <= N; ++ i) {
                        //In first rectangle
                        if (x[x1] <= x[i] && x[i] <= x[x1] + R &&
                            y[y1] <= y[i] && y[i] <= y[y1] + R) {
                            ++ cnt;
                            continue;
                        }

                        //In second rectangle
                        if (x[x2] <= x[i] && x[i] <= x[x2] + R &&
                            y[y2] <= y[i] && y[i] <= y[y2] + R) {
                            ++ cnt;
                            continue;
                        }
                    }
                    if (cnt > ans)
                        ans = cnt;
                }

    return ans;
}

int main()
{
    ofstream cout("data.out");

    int T = 0;
    cin >> T;

    for (int i = 1; i <= T; ++ i)
        cout << "Case #" << i << ": " << test() << '\n';

    cin.close();
    cout.close();
    return 0;
}
