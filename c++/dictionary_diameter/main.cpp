#include <bits/stdc++.h>

using namespace std;

// Checks whether a word is all lowercase letters
bool checkValid(const string &word) {
    for (auto ch: word)
        if (!islower(ch))
            return false;
    return true;
}

// Reads the dictionary
// Can change input and output sources in main
set <string> dict;
void readDict() {
    string word;
    while (cin >> word)
        if (checkValid(word))
            dict.insert(word);
}

// Returns the neighbors of a given word
vector <string> &findNeigh(const string &word) {
    static map <string, vector <string> > neighbors;
    if (!neighbors.count(word)) {
        for (int i = 0; i < static_cast <int>(word.size()); ++ i)
            for (char ch = 'a'; ch <= 'z'; ++ ch) {
                string aux = word;
                aux[i] = ch;
                if (dict.count(aux))
                    neighbors[word].push_back(aux);
            }
    }
    return neighbors[word];
}

// Distances and parent pointers (global
// variables used mainly by the BFS routine)
map <string, int> dist;
map <string, string> father;

// Outputs the path found by BFS by following parent pointers
void printSol(const string &word) {
    if (dist[word] == 1)
        cout << word;
    else {
        printSol(father[word]);
        cout << ", " << word;
    }
}

// BFS, find the eccentricity of a given word
// Can also print one shortest path of that length
// (disabled by default)
int bfs(string word, const bool shouldPrint = false) {
    queue <string> q;
    dist.clear(), father.clear();

    q.push(word), dist[word] = 1;
    while (!q.empty()) {
        word = q.front();
        q.pop();
        for (const string &it: findNeigh(word))
            if (!dist[it]) {
                dist[it] = dist[word] + 1;
                father[it] = word;
                q.push(it);
            }
    }

    if (shouldPrint) {
        cout << "Optimal solution of length " << dist[word] << " found:" << endl;
        printSol(word);
    }
    return dist[word];
}

int main() {
    // Change the input and output file names:
    assert(freopen("knuth_words.txt", "r", stdin));
    assert(freopen("output_knuth.txt", "w", stdout));

    // Reads the dictionary
    readDict();

    // Perform the BFS from all words of the dictionary
    int maxEc = 0;
    string maxEcWord;
    for (const string &word: dict) {
        int eccentricity = bfs(word);
        if (eccentricity > maxEc) {
            maxEc = eccentricity;
            maxEcWord = word;
        }

        // Show progress to the user
        static int i = 0;
        cerr << "Completed " << (++ i) << " / " << dict.size() << endl;
    }

    // Perform BFS again and print
    // the answer path
    bfs(maxEcWord, true);
    return 0;
}
