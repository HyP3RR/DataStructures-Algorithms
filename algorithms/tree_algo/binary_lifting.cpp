#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;

vector<vector<int>> adj;
// adjacency list of tree

constexpr int jmp = 20;
int up[N][jmp];

void dfs(int s, int par) {
    up[s][0] = par;
    for (auto v : adj[s]) {
        if (v != par)
            dfs(v, s);
    }
}

int main() {
    int n;
    cin >> n;
    adj.resize(n); // updates size to match n!
    /*
    fill adjacency list, n-1 edges
    */
    memset(
        up, -1,
        sizeof(up)); // smart to initialise up by -1 for no parent in start...
    // memset works at byte level -> avoid memset with double etc...
    // lesser chances of UB/errors.
    dfs(0, -1);
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i < n; i++) {
            if (up[i][j - 1] != -1)
                up[i][j] =
                    up[up[i][j - 1]][j - 1]; // double jump to get 2^j ancestor

            // no 2^j ancestor -> -1
        }
    }
}