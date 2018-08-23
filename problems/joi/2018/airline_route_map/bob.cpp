// Probabilistic solution with at most 11 extra nodes
#include "Boblib.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

const int NMAX = 1100;
bool graphAdjMat[NMAX][NMAX];

void Bob(int V, int U, int C[], int D[]) {
    // Graph
    vector <vector <int> > graph(V, vector <int>());
    for (int i = 0; i < U; ++ i) {
        graph[C[i]].push_back(D[i]);
        graph[D[i]].push_back(C[i]);
        graphAdjMat[C[i]][D[i]] = graphAdjMat[D[i]][C[i]] = true;
    }

    // Map
    const int N = V - 11;
    vector <pair <int, int> > mapEdges;

    mt19937 mt(123);
    uniform_int_distribution <int> dist(0, 1);
    int labels[10][10];
    int degs[10] = {0};
    for (int i = 0; i < 10; ++ i) {
        ++ degs[i];
        for (int j = 0; j < N; ++ j) {
            if (j & (1 << i)) {
                ++ degs[i];
			}
		}
	}

    for (int i = 0; i < 10; ++ i) {
        for (int j = 0; j < i; ++ j) {
            const bool val = dist(mt);
            labels[i][j] = val;
            if (val)
                ++ degs[i], ++ degs[j];
        }
    }

    // Identify helper node
    int node = -1;
    vector <int> v;
    for (int i = 0; i < V; ++ i) {
        if (graph[i].size() == 10) {
            bool found = false;
            function <void(int)> backtr = [&](int pos) {
                if (pos > 0) {
                    if (graph[v.back()].size() != degs[pos - 1])
                        return ;
                    for (int index = 0; index + 1 < pos; ++ index)
                        if (graphAdjMat[v[index]][v[pos - 1]] != labels[pos - 1][index])
                            return ;
                }

                if (pos == 10) {
                    found = true;
                    return ;
                }

                for (int index = 0; index < static_cast <int>(graph[i].size()); ++ index) {
                    if (found)
                        break;
                    const int nd = graph[i][index];
                    swap(graph[i][index], graph[i].back());
                    graph[i].pop_back();
                    v.push_back(nd);
                    backtr(pos + 1);
                    if (!found)
                        v.pop_back();
                    graph[i].push_back(nd);
                    swap(graph[i][index], graph[i].back());
                }
            };

            backtr(0);
            if (found) {
                node = i;
                break;
            }
        }
    }

    // Find shuffle used
    set <int> specials = {node};
    for (int i = 0; i < 10; ++ i) {
        const int node = v[i];
        specials.insert(node);
    }
    vector <int> perm(V);
    for (int i = 0; i < 10; ++ i) {
        const int node = v[i];
        for (auto it: graph[node]) {
            if (!specials.count(it)) {
                perm[it] += (1 << i);
            }
        }
    }
	
    // Reconstruct edges
    for (int i = 0; i < V; ++ i)
        if (!specials.count(i))
            for (auto it: graph[i])
                if (!specials.count(it) && i < it)
                    mapEdges.push_back(make_pair(perm[i], perm[it]));

    // Send graph
    const int M = mapEdges.size();
    InitMap(N, M);
    for (int i = 0; i < M; ++ i)
        MakeMap(mapEdges[i].first, mapEdges[i].second);
}
