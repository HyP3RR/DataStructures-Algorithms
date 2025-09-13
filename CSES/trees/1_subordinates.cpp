#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 3;
int n;
vector<int> par(N, 0);
vector<int> dp(N, 0);
vector<int> adj[N];

void dfs(int s, int p) {
    for (auto &v : adj[s]) {
        if (v == p)
            continue;

        dfs(v, s);
        dp[s] += dp[v] + 1; // count the child node itself.
    }
}

// 4-2-1-3-5
int main() {
    /*
    basic dp to add sizes
    */
    cin >> n;
    for (int i = 2; i <= n; i++)
        cin >> par[i];
    for (int i = 2; i <= n; i++) {
        adj[i].push_back(par[i]);
        adj[par[i]].push_back(i);
    }

    dfs(1, -1);
    for (int i = 1; i <= n; i++)
        cout << dp[i] << " ";
}
