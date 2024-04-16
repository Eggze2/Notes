#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class UnionFind {
public:
    vector<int> father;
    vector<int> size;

    // Constructor
    UnionFind(int n) {
        father.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++) {
            father[i] = i;
            size[i] = 1;
        }
    }

    // Find operation
    int Find(int i) {
        vector<int> help;
        while (i != father[i]) {
            help.push_back(i);
            i = father[i];
        }
        for (auto v : help) {
            father[v] = i;
        }
        return i;
    }

    // Union operation
    void Union(int i, int j) {
        int fi = Find(i);
        int fj = Find(j);
        if (fi != fj) {
            if (size[fi] >= size[fj]) {
                father[fj] = fi;
                size[fi] += size[fj];
            }
            else {
                father[fi] = fj;
                size[fj] += size[fi];
            }
        }
    }
};

int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
    int n = graph.size();

    vector<bool> virus(n, false);
    for (auto i : initial) {
        virus[i] = true;
    }

    UnionFind uf(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1 && !virus[i] && !virus[j]) {
                uf.Union(i, j);
            }
        }
    }

    vector<int> infect(n, -1);
    for (auto v : initial) {
        for (int next = 0; next < n; next++) {
            if (v != next && !virus[next] && graph[v][next] == 1) {
                int f = uf.Find(next);
                if (infect[f] == -1) {
                    infect[f] = v;
                }
                else if (infect[f] != -2 && infect[f] != v) {
                    infect[f] = -2;
                }
            }
        }
    }

    vector<int> cnt(n, 0);
    for (int i = 0; i < n; i++) {
        if (infect[i] >= 0) {
            cnt[infect[i]] += uf.size[i];
        }
    }

    sort(initial.begin(), initial.end());
    int ans = initial[0];
    int count = cnt[ans];
    for (auto i : initial) {
        if (cnt[i] > count) {
            ans = i;
            count = cnt[i];
        }
    }

    return ans;
}

int main() {
    vector<vector<int>> graph = { {1, 1, 0}, {1, 1, 0}, {0, 0, 1} };
    vector<int> initial = { 0, 1 };

    cout << minMalwareSpread(graph, initial) << endl;

    return 0;
}