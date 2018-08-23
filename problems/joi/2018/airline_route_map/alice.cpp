// Probabilistic solution with at most 11 extra nodes
#include "Alicelib.h"
#include <bits/stdc++.h>

using namespace std;

void Alice(int N, int M, int A[], int B[]) {
    // Graph
    const int V = N + 11;
    vector <pair <int, int> > edges;
    for (int i = 0; i < M; ++ i)
        edges.emplace_back(A[i], B[i]);

    // Encode in binary
    for (int i = 0; i < 10; ++ i) {
        for (int j = 0; j < N; ++ j) {
            if (j & (1 << i)) {
                edges.emplace_back(N + i, j);
            }
        }
        // Add control node edges
        edges.emplace_back(N + 10, N + i);
    }

    // Generate random vector
    mt19937 mt(123);
    uniform_int_distribution <int> dist(0, 1);

    // Add clique
    for (int i = 0; i < 10; ++ i) {
        for (int j = 0; j < i; ++ j) {
            const bool val = dist(mt);
            if (val)
                edges.emplace_back(N + j, N + i);
        }
    }

    // Send graph
    const int U = edges.size();
    InitG(V, U);
    for (int i = 0; i < U; ++ i) {
        MakeG(i, edges[i].first, edges[i].second);
    }
}
