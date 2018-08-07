#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

const int NMAX = 100 + 5;

//Graph
vector <pair <pair <int, int>, int> > graph[NMAX][NMAX];
void addEdge(pair <int, int> a, pair <int, int> b, int place) {
    graph[a.first][a.second].push_back(make_pair(b, place));
}

queue <pair <int, int> > q;
pair <pair <int, int>, int> father[NMAX][NMAX];

//Strings
int N;
int len[NMAX];
string str[NMAX];

int pi[NMAX];

void computePi(const int len, const string &str) {
    int k = 0;
    for (int i = 2; i <= len; ++ i) {
        while (k && str[k + 1] != str[i])
            k = pi[k];
        if (str[k + 1] == str[i])
            ++ k;
        pi[i] = k;
    }
}

vector <int> sol;

void print(pair <int, int> node) {
    if (node.first == -1)
        return ;

    print(father[node.first][node.second].first);
    sol.push_back(father[node.first][node.second].second);
}

int main()
{
    ios_base :: sync_with_stdio(false);

    //Read strings
    cin >> N;
    for (int i = 1; i <= N; ++ i) {
        cin >> str[i];
        len[i] = str[i].size();
        str[i] = " " + str[i];
    }

    //Compute graph by means of KMP
    for (int i = 1; i <= N; ++ i) {
        computePi(len[i], str[i]);

        for (int j = 1; j <= N; ++ j)
            if (i != j) {
                int k = 0;
                for (int l = 1; l <= len[j]; ++ l) {
                    while (k && str[i][k + 1] != str[j][l])
                        k = pi[k];
                    if (str[i][k + 1] == str[j][l])
                        ++ k;

                    if (k == len[i])
                        addEdge(make_pair(j, l - len[i] + 1), make_pair(j, l + 1), i);
                }

                while (k) {
                    addEdge(make_pair(j, len[j] - k + 1), make_pair(i, k + 1), i);
                    k = pi[k];
                }
            }
    }

    //Find path in graph
    for (int i = 1; i <= N; ++ i) {
        q.push(make_pair(i, 1));
        father[i][1] = make_pair(make_pair(-1, -1), i);
    }

    pair <int, int> node;
    while (!q.empty()) {
        node = q.front();
        if (node.second == len[node.first] + 1)
            break;
        q.pop();

        for (auto it: graph[node.first][node.second])
            if (father[it.first.first][it.first.second].first.first == 0) {
                q.push(it.first);
                father[it.first.first][it.first.second] = make_pair(node, it.second);
            }
    }

    for (int i = 1; i <= N; ++ i)
        str[i] = str[i].substr(1, str[i].size() - 1);

    if (q.empty())
        cout << "NO\n";
    else {
        cout << "YES\n";

        print(node);

        //Build the 2 strings
        string a, b;
        for (auto it: sol) {
            if (a.size() <= b.size())
                a += str[it];
            else
                b += str[it];
        }

        cout << a << '\n';
    }
    return 0;
}
