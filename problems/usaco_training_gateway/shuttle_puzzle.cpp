/*
ID: andreip3
LANG: C++14
TASK: shuttle
*/
#include <bits/stdc++.h>

using namespace std;

int N;
map <string, pair <string, int> > father;
queue <string> q;

void bfs() {
    string start, finish;
    for (int i = 0; i < N; ++ i)
        start += 'W', finish += 'B';
    start += ' ', finish += ' ';
    for (int i = 0; i < N; ++ i)
        start += 'B', finish += 'W';
    N = 2 * N  + 1;

    q.push(start);

    while (!q.empty()) {
        const string str = q.front();
        q.pop();

        if (str == finish)
            break;

        string newStr;
        for (int i = 0; i < N; ++ i)
            if (str[i] == 'W') {
                if (i + 1 < N && str[i + 1] == ' ') {
                    newStr = str;
                    swap(newStr[i], newStr[i + 1]);
                    if (!father.count(newStr)) {
                        father[newStr] = {str, i};
                        q.push(newStr);
                    }
                }
                else if (i + 2 < N && str[i + 1] == 'B' && str[i + 2] == ' ') {
                    newStr = str;
                    swap(newStr[i], newStr[i + 2]);
                    if (!father.count(newStr)) {
                        father[newStr] = {str, i};
                        q.push(newStr);
                    }
                }
            }
            else if (str[i] == 'B') {
                if (i - 1 >= 0 && str[i - 1] == ' ') {
                    newStr = str;
                    swap(newStr[i], newStr[i - 1]);
                    if (!father.count(newStr)) {
                        father[newStr] = {str, i};
                        q.push(newStr);
                    }
                }
                else if (i - 2 >= 0 && str[i - 1] == 'W' && str[i - 2] == ' ') {
                    newStr = str;
                    swap(newStr[i], newStr[i - 2]);
                    if (!father.count(newStr)) {
                        father[newStr] = {str, i};
                        q.push(newStr);
                    }
                }
            }
    }

    vector <int> sol;
    while (finish != start) {
        sol.push_back(father[finish].second);
        finish = father[finish].first;
    }

    reverse(sol.begin(), sol.end());
    for (int i = 0; i < sol.size(); ++ i)
        cout << sol[i] + 1 << " \n"[i + 1 == sol.size() || (i + 1) % 20 == 0];
}

int main() {
    freopen("shuttle.in", "r", stdin);
    freopen("shuttle.out", "w", stdout);
    cin >> N;
    bfs();
    return 0;
}
