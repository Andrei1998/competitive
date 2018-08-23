#include <bits/stdc++.h>

using namespace std;

const int NMAX = 10000 + 5;

int N, M; // R, C
int Vehicles; // Fleet
int Rides; // Rides
int Bonus;
int Time;

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0):
        x(_x), y(_y) {}
    friend istream& operator>>(istream& i, Point &p) {
        i >> p.x >> p.y;
        return i;
    }
};

inline int dist(const Point &a, const Point &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

bool used[NMAX];
Point startPoint[NMAX], finishPoint[NMAX];
int startTime[NMAX], finishTime[NMAX];

int main() {
    const string test = "b";
    if (test == "a") {
        freopen("a_example.in", "r", stdin);
        freopen("a_example.out", "w", stdout);
    }
    else if (test == "b") {
        freopen("b_should_be_easy.in", "r", stdin);
        freopen("b_should_be_easy.out", "w", stdout);
    }
    else if (test == "c") {
        freopen("c_no_hurry.in", "r", stdin);
        freopen("c_no_hurry.out", "w", stdout);
    }
    else if (test == "d") {
        freopen("d_metropolis.in", "r", stdin);
        freopen("d_metropolis.out", "w", stdout);
    }
    else if (test == "e") {
        freopen("e_high_bonus.in", "r", stdin);
        freopen("e_high_bonus.out", "w", stdout);
    }
    else
        assert(0);

    cin >> N >> M;
    cin >> Vehicles;
    cin >> Rides;
    cin >> Bonus;
    cin >> Time;
    for (int i = 1; i <= Rides; ++ i)
        cin >> startPoint[i] >> finishPoint[i] >> startTime[i] >> finishTime[i];

    for (int i = 1; i <= Vehicles; ++ i) {
        Point where(0, 0);
        int tmp = 0;
        vector <int> path;
        while (1) {
            long long int associated = 1E18;
            long long int quickest = 1E18;
            int who = -1;
            for (int j = 1; j <= Rides; ++ j)
                if (!used[j]) {
                    const int reach = max(startTime[j], tmp + dist(where, startPoint[j]));
                    if (reach + dist(startPoint[j], finishPoint[j]) <= finishTime[j]) {
                        const int tmpTaken = reach + dist(startPoint[j], finishPoint[j]) - tmp;
                        int sortCr = dist(startPoint[j], finishPoint[j]);

                        // if (reach == startTime[j])
                        //     sortCr -= 35 * Bonus;

                        if (sortCr < quickest) {
                            quickest = sortCr;
                            associated = tmpTaken;
                            who = j;
                        }
                    }
                }
            if (who == -1)
                break;
            else {
                used[who] = true;
                path.push_back(who - 1);
                where = finishPoint[who];
                tmp += associated;
            }
        }

        cout << path.size();
        cerr << "Done = " << i << " / " << Vehicles << endl;
        for (auto it: path)
            cout << ' ' << it;
        cout << endl;
    }

    return 0;
}
