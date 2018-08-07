#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
#include <vector>
#include <string>

using namespace std;

map <vector <string>, string> Map;

stack <string> stk;

vector <string> v;
string str;

void compress() {
    v.clear();
    stk.pop();

    while (stk.top() != "(") {
        v.push_back(stk.top());
        stk.pop();
    }

    stk.pop();

    sort(v.begin(), v.end());
    stk.push(Map[v]);
}

void solve() {
    int level = 0;

    while (1) {
        cin >> str;
        if (str == "+")
            continue;
        stk.push(str);

        if (str != ")") {
            if (str == "(")
                ++ level;
        }
        else {
            -- level;
            compress();
        }

        if (!level) {
            cout << stk.top() << '\n';
            return ;
        }
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    int N = 0;
    cin >> N;

    for (int i = 1; i <= N; ++ i) {
        v.clear();
        while (1) {
            cin >> str;
            if (str == ")")
                break;
            else if (str != "(" && str != "+")
                v.push_back(str);
        }

        cin >> str; // =
        cin >> str;

        sort(v.begin(), v.end());
        Map[v] = str;
    }

    int M = 0;
    cin >> M;

    while (M --)
        solve();
    return 0;
}
