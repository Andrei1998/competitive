#include <bits/stdc++.h>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
using namespace std;

int T, N, C;

// A bit more hardcoded than necessary, see implementation of solve2 for a more abstract approach
void solve1() {
    const vector <string> names = {"in",  "in2", "in3", "in4",
                                   "in5", "in6", "in7", "in8",
                                   "in9", "in10", "in11"};
    int level = 0;
    while (N > 2) {
        int pos = 0;
        for (int i = 0; i < N; i += 2) {
            if (i + 1 < N)
                cout << names[level + 1] << "[" << pos << "] = " << names[level] << "[" << i << "] + " << names[level] << "[" << i + 1 << "]" << endl;
            else
                cout << names[level + 1] << "[" << pos << "] = " << names[level] << "[" << i << "] + 0" << endl;
            ++pos;
        }
        N = pos, ++level;
    }
    if (N == 2)
        cout << "out[0] = " << names[level] << "[" << 0 << "] + " << names[level] << "[" << 1 << "]" << endl;
}

void solve2() {
    static map <pair <int, int>, string> name; // name[i, j] = variable which represents sum of numbers i ... j
    static map <pair <int, int>, bool> made; // made[i, j] = was name[i, j] constructed already?

    auto getName = [](int l, int r) {
        if (!name.count(make_pair(l, r))) {
            const int nr = name.size() + 1;
            name[make_pair(l, r)] = "var" + SSTR(nr) + "[0]";
        }
        return name[make_pair(l, r)];
    };

    // Edge case
    cout << "out[0] = in[0] + 0" << endl;

    for (int i = 0; i < N; ++i) {
        name[make_pair(i, i)] = "in["  + SSTR(i) + "]";
        if (i > 0)
            name[make_pair(0, i)] = "out[" + SSTR(i) + "]";
    }
    auto printMake = [&](int l, int mid, int r) {
        cout << getName(l, r) << " = " << getName(l, mid) << " + " << getName(mid + 1, r) << endl;
        made[make_pair(l, r)] = true;
    };

    function <void(int, int)> buildSegmentTree = [&](int l, int r) {
        if (l < r) {
            const int mid = (l + r) / 2;
            buildSegmentTree(l, mid);
            buildSegmentTree(mid + 1, r);
            printMake(l, mid, r);
        }
    };
    function <void(int, int, int)> solveQuerySegmentTree = [&](int l, int r, int queryR) {
        if (queryR < r) {
            const int mid = (l + r) / 2;
            if (queryR <= mid) {
                solveQuerySegmentTree(l, mid, queryR);
            }
            else {
                solveQuerySegmentTree(mid + 1, r, queryR);
                printMake(l, mid, queryR);
            }
        }
    };

    buildSegmentTree(0, N - 1);
    for (int i = 1; i < N; ++i) {
        if (i % 3 == 0) {
            solveQuerySegmentTree(0, N - 1, i);
        }
        else {
            if (!made[make_pair(0, i)])
                printMake(0, i - 1, i);
        }
    }
}

void solve3() {
    static map <pair <int, int>, string> nameSum; // nameSum[i, j] = variable which represents sum of numbers i ... j
    static map <pair <int, int>, string> namePref; // namePref[i, j] = variable which represents best prefix of numbers i ... j
    static map <pair <int, int>, string> nameSuf; // nameSuf[i, j] = variable which represents best suffix of numbers i ... j
    static map <pair <int, int>, string> nameBest; // nameBest[i, j] = variable which represents best continuous subsequence of numbers i ... j
    static int allNames = 0;

    auto getNewName = [&]() {
        ++allNames;
        const string newName = "var" + SSTR(allNames) + "[0]";
        return newName;
    };
    auto getName = [&](int l, int r, map <pair <int, int>, string> &name) {
        if (!name.count(make_pair(l, r)))
            name[make_pair(l, r)] = getNewName();
        return name[make_pair(l, r)];
    };

    auto printMake = [&](int l, int mid, int r) {
        // Compute sum
        cout << getName(l, r, nameSum) << " = " << getName(l, mid, nameSum) << " + " << getName(mid + 1, r, nameSum) << endl;

        // Compute best suffix
        const string sumRight = getNewName();
        cout << sumRight << " = " << getName(l, mid, nameSuf) << " + " << getName(mid + 1, r, nameSum) << endl;
        cout << getName(l, r, nameSuf) << " = " << sumRight << " max " << getName(mid + 1, r, nameSuf) << endl;

        // Compute best prefix
        const string sumLeft = getNewName();
        cout << sumLeft << " = " << getName(mid + 1, r, namePref) << " + " << getName(l, mid, nameSum) << endl;
        cout << getName(l, r, namePref) << " = " << sumLeft << " max " << getName(l, mid, namePref) << endl;

        // Compute  best continuous subsequence
        const string bestAlone = getNewName();
        const string bestMid = getNewName();
        cout << bestAlone  << " = " << getName(l, mid, nameBest) << " max " << getName(mid + 1, r, nameBest) << endl;
        cout << bestMid << " = " << getName(l, mid, nameSuf) << " + " << getName(mid + 1, r, namePref) << endl;
        cout << getName(l, r, nameBest) << " = " << bestAlone << " max " << bestMid << endl;
    };
    function <void(int, int)> buildSegmentTree = [&](int l, int r) {
        if (l < r) {
            const int mid = (l + r) / 2;
            buildSegmentTree(l, mid);
            buildSegmentTree(mid + 1, r);
            printMake(l, mid, r);
        }
    };

    // Initialize a few names
    for (int i = 0; i < N; ++ i)
        nameSum[make_pair(i, i)] = namePref[make_pair(i, i)] = nameSuf[make_pair(i, i)] = nameBest[make_pair(i, i)] = "in[" + SSTR(i) + "]";
    buildSegmentTree(0, N - 1);
    cout << "out[0] = 0 max " << getName(0, N - 1, nameBest) << endl;
}

int main() {
    cin >> T >> N >> C;
    //T = 1, N = 7,    C = 3;  // Test 0
    //T = 1, N = 256,  C = 8;  // Test 1
    //T = 1, N = 1093, C = 11; // Test 2

    //T = 2, N = 7,   C = 5;  // Test 3
    //T = 2, N = 128, C = 13; // Test 4
    //T = 2, N = 371, C = 15; // Test 5

    //T = 3, N = 7,   C = 15; // Test 6
    //T = 3, N = 64,  C = 31; // Test 7
    //T = 3, N = 110, C = 35; // Test 8
    //T = 3, N = 124, C = 35; // Test 9

    if (T == 1) {
        if (N == 7)
            freopen("output000.txt", "w", stdout);
        else if (N == 256)
            freopen("output001.txt", "w", stdout);
        else if (N == 1093)
            freopen("output002.txt", "w", stdout);
        else // Should not happen
            assert(false);
        solve1();
    }
    else if (T == 2) {
        if (N == 7)
            freopen("output003.txt", "w", stdout);
        else if (N == 128)
            freopen("output004.txt", "w", stdout);
        else if (N == 371)
            freopen("output005.txt", "w", stdout);
        else // Should not happen
            assert(false);
        solve2();
    }
    else if (T == 3) {
        if (N == 7)
            freopen("output006.txt", "w", stdout);
        else if (N == 64)
            freopen("output007.txt", "w", stdout);
        else if (N == 110)
            freopen("output008.txt", "w", stdout);
        else if (N == 124)
            freopen("output009.txt", "w", stdout);
        else // Should not happen
            assert(false);
        solve3();
    }
    else // Should not happen
        assert(false);
    return 0;
}
