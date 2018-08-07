#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

inline void toString(string &str, int nr) {
    while (nr) {
        str += (char)((nr % 10) + '0');
        nr /= 10;
    }
    reverse(str.begin(), str.end());
}

inline void toInt(int &ans, const string &str) {
    ans = 0;
    for (auto it: str) {
        ans *= 10;
        ans += (it - '0');
    }
}

void getNeighbours(vector <int> &ans, int nr) {
    string str;
    toString(str, nr);

    //Change
    for (int i = 0; i < str.size(); ++ i) {
        for (char ch = '0' + (i == 0); ch <= str[i]; ++ ch)
            if (ch != str[i]) {
                string auxStr = str;
                auxStr[i] = ch;
                int intAuxStr;
                toInt(intAuxStr, auxStr);
                ans.push_back(intAuxStr);
            }
        }

    //Erase
    if (str.size() > 1)
        for (int i = 0 + (str[1] == '0'); i < str.size(); ++ i) {
            string auxStr = str;
            auxStr.erase(auxStr.begin() + i);

            int intAuxStr;
            toInt(intAuxStr, auxStr);
            ans.push_back(intAuxStr);
        }

    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
}

int diff(const string &A, const string &B) {
    int ans = 0;
    for (int i = 0; i < 4; ++ i)
        ans += (A[i] != B[i]);
    return ans;
}

const int NMAX = 65536 + 5;
string strs[NMAX];

int ans[5];

int main()
{
    ios_base :: sync_with_stdio(false);

    int N;
    cin >> N;

    for (int i = 1; i <= N; ++ i)
        cin >> strs[i];

    vector <int> neigh;
    for (int i = 1; i <= N; ++ i) {
        neigh.clear();
        getNeighbours(neigh, i);
        for (auto it: neigh)
            ++ ans[diff(strs[i], strs[it])];
    }

    for (int i = 1; i < 5; ++ i)
        cout << ans[i] << " \n"[i == 4];
    return 0;
}
