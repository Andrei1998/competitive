/*
ID: andreip3
LANG: C++14
TASK: window
*/
#include <bits/stdc++.h>

using namespace std;

struct Window {
    char label;
    int x1, y1, x2, y2;
    Window(char _label = '?', int _x1 = 0, int _y1 = 0, int _x2 = 0, int _y2 = 0):
        label(_label), x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
    bool operator==(const Window &arg) const {
        return label == arg.label;
    }
};

vector <Window> windows;

static inline int find(const char label) {
    return find(windows.begin(), windows.end(), label) - windows.begin();
}
static inline void destroy(const char label) {
    windows.erase(windows.begin() + find(label));
}
static inline void top(const char label) {
    Window w = windows[find(label)];
    destroy(label);
    windows.push_back(w);
}
static inline void bottom(const char label) {
    Window w = windows[find(label)];
    destroy(label);
    windows.push_back(Window());
    for (int i = windows.size() - 1; i; -- i)
        windows[i] = windows[i - 1];
    windows[0] = w;
}

static long double solve(const char label) {
    const int where = find(label);

    vector <int> allX, allY;
    for (int i = where; i < windows.size(); ++ i) {
        const Window &w = windows[i];
        allX.push_back(w.x1), allX.push_back(w.x2);
        allY.push_back(w.y1), allY.push_back(w.y2);
    }

    // Compress coordinates
    const auto normAll = [&](vector <int> &v) {
        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());
    };
    normAll(allX), normAll(allY);

    // Build Mars
    int x1, y1, x2, y2;
    auto normWindow = [&](const Window &w) {
        x1 = lower_bound(allX.begin(), allX.end(), w.x1) - allX.begin() + 1;
        x2 = lower_bound(allX.begin(), allX.end(), w.x2) - allX.begin() + 1;
        y1 = lower_bound(allY.begin(), allY.end(), w.y1) - allY.begin() + 1;
        y2 = lower_bound(allY.begin(), allY.end(), w.y2) - allY.begin() + 1;
    };

    vector <vector <int> > mars(allX.size() + 1, vector <int>(allY.size() + 1, 0));
    for (int i = where + 1; i < windows.size(); ++ i) {
        const Window &w = windows[i];
        normWindow(w);
        ++ mars[x1][y1], -- mars[x1][y2], -- mars[x2][y1], ++ mars[x2][y2];
    }
    for (int i = 1; i <= allX.size(); ++ i)
        for (int j = 1; j <= allY.size(); ++ j)
            mars[i][j] += mars[i - 1][j] + mars[i][j - 1] - mars[i - 1][j - 1];

    // Verify main window
    const Window &mainWindow = windows[where];
    normWindow(mainWindow);
    long long int coveredArea = 0, allArea = 0;
    for (int x = x1; x < x2; ++ x)
        for (int y = y1; y < y2; ++ y) {
            const int cellArea = 1LL * (allX[x] - allX[x - 1]) * (allY[y] - allY[y - 1]);
            if (!mars[x][y])
                coveredArea += cellArea;
            allArea += cellArea;
        }
    return 100.0L * coveredArea / allArea;
}

int main() {
    freopen("window.in", "r", stdin);
    freopen("window.out", "w", stdout);

    char type, aux, label;
    while (cin >> type >> aux >> label >> aux) {
        if (type == 'w') {
            int x1, y1, x2, y2;
            cin >> x1 >> aux >> y1 >> aux >> x2 >> aux >> y2 >> aux;

            int minX = min(x1, x2);
            int maxX = max(x1, x2);
            int minY = min(y1, y2);
            int maxY = max(y1, y2);

            windows.push_back(Window(label, minX, minY, maxX, maxY));
        }
        else if (type == 's')
            cout << fixed << setprecision(3) << solve(label) << '\n';
        else if (type == 't')
            top(label);
        else if (type == 'd')
            destroy(label);
        else if (type == 'b')
            bottom(label);
        else
            assert(1);
    }
    return 0;
}
