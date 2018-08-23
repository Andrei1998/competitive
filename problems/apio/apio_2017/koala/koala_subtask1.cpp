#include "koala.h"
#include <iostream>

using namespace std;

int minValue(int N, int W) {
    int B[100] = {0};
    int R[100];

    B[0] = 1;
    playRound(B, R);

    for (int i = 0; i < N; ++ i)
        if (R[i] <= B[i])
            return i;
}

int maxValue(int N, int W) {
    return 0;
}

int greaterValue(int N, int W) {
    return 0;
}

void allValues(int N, int W, int *P) {
    ;
}
