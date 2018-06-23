#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100 + 5;

int N;
vector <int> model_graph[NMAX];
vector <int> input_graph[NMAX];

typedef unsigned long long int ulint;

int lvl[] = {62, 132, 49, 29, 65, 30, 13, 40, 123};

ulint hashVec(int levels, int node, vector <int> dists, vector <int> graph[]) {
    vector <ulint> x = {dists[node - 1]};
    for (auto it: graph[node]) {
        if (levels == 0)
            x.push_back(dists[it - 1]);
        else
            x.push_back(hashVec(levels - 1, it, dists, graph));
    }
    sort(x.begin() + 1, x.end());
    ulint h = 0;
    for (auto it: x) {
        h *= lvl[levels];
        h += it;
    }
    return h;
}

ulint getHash(int node, vector <int> graph[]) {
    queue <int> q;
    vector <bool> vis(N + 1, false);
    vector <int> dist(N, 0);

    q.push(node);
    vis[node] = true;
    while (!q.empty()) {
        const int node = q.front();
        q.pop();
        for (auto it: graph[node])
            if (!vis[it]) {
                vis[it] = true;
                dist[it - 1] = 1 + dist[node - 1];
                q.push(it);
            }
    }

    vector <vector <ulint> > ans(N, vector <ulint>());
    for (int i = 0; i < N; ++ i) {
        ans[i].push_back(dist[i]);
        for (auto it: graph[i + 1])
            ans[i].push_back(hashVec(1, it, dist, graph));
        sort(ans[i].begin() + 1, ans[i].end());
    }
    sort(ans.begin(), ans.end());

    ulint h = 0;
    for (auto it: ans)
        for (auto it2: it) {
            h *= 62;
            h += it2;
        }
    return h;
}

void hardCode10() {
    N = 10;
    model_graph[1]  = {2, 3, 4, 5};
    model_graph[2]  = {1, 3, 4, 6};
    model_graph[3]  = {1, 2, 5, 7};
    model_graph[4]  = {1, 2, 6, 8};
    model_graph[5]  = {1, 3, 8, 9};
    model_graph[6]  = {2, 4, 9, 10};
    model_graph[7]  = {3, 8, 9, 10};
    model_graph[8]  = {4, 5, 7, 10};
    model_graph[9]  = {5, 6, 7, 10};
    model_graph[10] = {6, 7, 8, 9};
}

map <ulint, int> whichNode;

void generateMap() {
    //for (int i = 1; i <= N; ++ i) {
    //    auto aux = getHash(i, model_graph);
    //    whichNode[aux] = i;
    //}

    whichNode[2887582567447979266ULL] = 3;
    whichNode[3348015663647391378ULL] = 2;
    whichNode[4167516904265139714ULL] = 4;
    whichNode[9501969217743396482ULL] = 8;
    whichNode[9674004821287258242ULL] = 6;
    whichNode[13541544972755832682ULL] = 5;
    whichNode[13757370122413376758ULL] = 1;
    whichNode[15198461776219211122ULL] = 7;
    whichNode[17233749607643625362ULL] = 9;
    whichNode[17873747264999113974ULL] = 10;

    //for (auto it: whichNode)
    //    cout << "whichNode[" << it.first << "ULL] = " << it.second << ";" << endl;

    /*vector <ulint> hs;
    for (int i = 1; i <= N; ++ i) {
        hs.push_back(getHash(i, model_graph));
        assert(whichNode.count(hs.back()));
    }
    sort(hs.begin(), hs.end());
    for (auto it: hs)
        cout << it << endl;*/
}

int main() {
    hardCode10();
    generateMap();

    int T;
    cin >> T;

    for (int t = 1; t <= T; ++ t) {
        int L, U;
        cin >> L >> U;

        cout << N << endl;
        //vector <pair <int, int> > edges;
        for (int i = 1; i <= N; ++ i)
            for (auto it: model_graph[i])
                if (i < it) {
                    cout << i << ' ' << it << endl;
                    //edges.emplace_back(i, it);
                }

        //assert(edges.size() == 2 * N);

        //vector <int> _p;
        //for (int i = 0; i <= N; ++ i)
        //    _p.push_back(i);
        //random_shuffle(_p.begin() + 1, _p.end());

        cin >> N;
        for (int i = 1; i <= N; ++ i)
            input_graph[i].clear();

        for (int i = 1; i <= 2 * N; ++ i) {
            int a, b;
            cin >> a >> b;
            input_graph[a].push_back(b);
            input_graph[b].push_back(a);
        }


        //for (auto it: edges)
        //    input_graph[_p[it.first]].push_back(_p[it.second]),
        //    input_graph[_p[it.second]].push_back(_p[it.first]);
        cout.flush();
        vector <int> p(N + 1, 0);
        for (int i = 1; i <= N; ++ i) {
            ulint h = getHash(i, input_graph);
            assert(whichNode.count(h));
            p[whichNode[h]] = i;
        }

        for (int i = 1; i < p.size(); ++ i)
            cout << p[i] << " \n"[i + 1 == p.size()];
        //for (int i = 0; i < p.size(); ++ i)
        //    cout << _p[i] << " \n"[i + 1 == p.size()];
        cout.flush();
    }

    return 0;
}
