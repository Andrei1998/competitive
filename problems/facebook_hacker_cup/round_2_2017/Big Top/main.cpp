#include <bits/stdc++.h>

#define double long double
using namespace std;

typedef long long int lint;

lint area(int D, int h0, int h1) {
    //Scale drawing by a factor of 4
    D *= 4;
    h0 *= 4;
    h1 *= 4;

    int h = (h0 + h1 - D) / 2;
    lint area;
    if (h < 0)
        area = 1LL * h0 * h0 / 2 + 1LL * h1 * h1 / 2;
    else {
        assert(h < h0);
        assert(h < h1);

        int x = (D - (h1 - h0)) / 2;
        assert(x > 0 && x < D);

        area = 1LL * x * (h + h0) / 2 + 1LL * (D - x) * (h + h1) / 2;
    }

    return area;
}

inline lint area(pair <int, int> p0, pair <int, int> p1) {
    if (p0 > p1)
        swap(p0, p1);
    return area(p1.first - p0.first, p0.second, p1.second);
}

//Is A over B?
bool dominates(pair <int, int> A, pair <int, int> B) {
    int xA = A.first, yA = A.second;
    int xB = B.first, yB = B.second;

    assert(xA != xB);

    if (xA > xB)
        return xA - xB <= yA - yB;
    else
        return xB - xA <= yA - yB;
}

const int NMAX = 800000 + 5;
const int XMAX = 10000000 + 15;

int N;

int Ax, Bx, Cx;
int Ah, Bh, Ch;

int x[NMAX];
int h[NMAX];

set <pair <int, int> > Set;
lint SetArea;

double test() {
    //Read
    cin >> N;
    cin >> x[1] >> Ax >> Bx >> Cx;
    cin >> h[1] >> Ah >> Bh >> Ch;

    for (int i = 2; i <= N; ++ i) {
        x[i] = (1LL * Ax * x[i - 1] + Bx) % Cx + 1;
        h[i] = (1LL * Ah * h[i - 1] + Bh) % Ch + 1;
    }

    //Solve
    Set.clear();
    Set.insert(make_pair(-2 * XMAX, 0));
    Set.insert(make_pair(2 * XMAX, 0));
    SetArea = 0;

    double ans = 0;
    for (int i = 1; i <= N; ++ i) {
        auto it = Set.insert(make_pair(x[i], h[i])).first;

        auto itB = (-- it); ++ it;
        auto itF = (++ it); -- it;

        assert(itF != Set.end());

        if (dominates(*itB, *it) || dominates(*itF, *it))
            Set.erase(it);
        else {
            SetArea -= area(*itB, *itF);

            //Remove backwards
            while (dominates(*it, *itB)) {
                pair <int, int> p0 = *itB;
                Set.erase(itB --);
                pair <int, int> p1 = *itB;
                SetArea -= area(p0, p1);
            }

            //Remove forward
            while (dominates(*it, *itF)) {
                pair <int, int> p0 = *itF;
                Set.erase(itF ++);
                pair <int, int> p1 = *itF;
                SetArea -= area(p0, p1);
            }

            //Add new area
            SetArea += area(*it, *itB);
            SetArea += area(*it, *itF);
        }
        //Add new area
        ans += SetArea / (4.0 * 4.0);
    }

    return ans;
}

int main()
{
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);

    int T = 0;
    cin >> T;

    for (int i = 1; i <= T; ++ i)
        cout << "Case #" << i << ": " << fixed << setprecision(8) << test() << '\n';
    return 0;
}
