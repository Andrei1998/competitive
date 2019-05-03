#include <bits/stdc++.h>

using namespace std;

void declare_variables() {
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            for (int k = 1; k <= 9; ++k) {
                cout << "(declare-const x" << i << j << k << " Bool)" << endl;
            }
        }
    }
}

using Clause = vector <tuple <int, int, int> >;
void print_clause(Clause &c) {
    cout << "(assert (or";
    for (const auto &it: c) {
        int i, j, k; tie(i, j, k) = it;
        cout << " x" << i << j << k;
    }
    cout << "))" << endl;
}

void add_constraints() {
    // Row & column constraints
    for (int i = 1; i <= 9; ++i) {
        for (int k = 1; k <= 9; ++k) {
            Clause row, column;
            for (int j = 1; j <= 9; ++j) {
                row.emplace_back(i, j, k);
                column.emplace_back(j, i, k);
            }
            print_clause(row);
            print_clause(column);
        }
    }
    // 3 x 3 block constraints
    for (int k = 1; k <= 9; ++k) {
        for (int u = 0; u <= 2; ++u) {
            for (int v = 0; v <= 2; ++v) {
                Clause c;
                for (int i = 1; i <= 3; ++i) {
                    for (int j = 1; j <= 3; ++j) {
                        c.emplace_back(3 * u + i, 3 * v + j, k);
                    }
                }
                print_clause(c);
            }
        }
    }
    // No square has two numbers constraints
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            for (int k1 = 1; k1 <= 9; ++k1) {
                for (int k2 = k1 + 1; k2 <= 9; ++k2) {
                    cout << "(assert (not (and x" << i << j << k1 << " x" << i << j << k2;
                    cout << ")))" << endl;
                }
            }
        }
    }

}

void add_pos_constraint(int i, int j, int k) {
    cout << "(assert x" << i << j << k << ")" << endl;
}


void add_hardcoded() {
    // Change matrix for different sudoku
    string mat[] = {
        ".2.5.1.9.",
        "8..2.3..6",
        ".3..6..7.",
        "..1...6..",
        "54.....19",
        "..2...7..",
        ".9..3..8.",
        "2..8.4..7",
        ".1.9.7.6."
    };
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (mat[i][j] != '.') {
                add_pos_constraint(i + 1, j + 1, mat[i][j] - '0');
            }
        }
    }
}

int sol[10][10];
void parse_and_print() {
    string ok, aux, var, value;
    cin >> ok;
    assert(ok == "sat");

    cin >> aux; // (model
    for (int cnt = 1; cnt <= 9 * 9 * 9; ++cnt) {
        cin >> aux; // (define-fun
        cin >> var; // xijk
        
        // xijk
        const int i = var[1] - '0';
        const int j = var[2] - '0';
        const int k = var[3] - '0';

        cin >> aux; // ()
        cin >> aux; // Bool

        cin >> value; // false) / true)
        if (value == "true)") {
            sol[i][j] = k;
        }
    }

    cin >> aux; // )
    
    // Solution will be in solution.out
    freopen("solution.out", "w", stderr);
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            cerr << sol[i][j] << " \n"[j == 9];
        }
    }
    
}

int main() {
    // Encoding will be in encoding.z3
    freopen("encoding.z3", "w", stdout);

    declare_variables();
    add_constraints();
    add_hardcoded();
    cout << "(check-sat)" << endl;
    cout << "(get-model)" << endl;
    
    // Run Z3, model will be in model.out
    system("z3 encoding.z3 >model.out");
    
    // Parse output and print solved puzzle
    freopen("model.out", "r", stdin);
    parse_and_print();
    
    // Solution:
    //
    //   4 2 6 5 7 1 3 9 8
    //   8 5 7 2 9 3 1 4 6
    //   1 3 9 4 6 8 2 7 5
    //   9 7 1 3 8 5 6 2 4
    //   5 4 3 7 2 6 8 1 9
    //   6 8 2 1 4 9 7 5 3
    //   7 9 4 6 3 2 5 8 1
    //   2 6 5 8 1 4 9 3 7
    //   3 1 8 9 5 7 4 6 2
    //
    // (b)
    //   To enumerate solutions we could adapt the same idea of invoking the Z3 solver:
    //   Call the solver once - this gives us one solution.
    //   Add constraints that we need a solution that differs from the one we got
    //   in at least one square.
    //   Invoke the solver again - possibly getting another solution.
    //   Add further new constraints that we need a solution that differs from the one
    //   we just got in at least one square.
    //   Continue on with this procedure until we no longer get solutions ...
    return 0;
}
