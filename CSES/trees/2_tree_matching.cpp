#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int>> adj;
vector<vector<int>> dp;

void dfs(int s, int p) {
    int maxi = 0;
    for (auto v : adj[s]) {
        if (v != p) {
            dfs(v, s);
            dp[s][0] += max(dp[v][0], dp[v][1]);
            dp[s][1] += dp[v][1];
            maxi = max(maxi, dp[v][0] - dp[v][1] + 1);
        }
    }
    dp[s][1] += maxi;
}

int main() {
    /*
    simple dp, dp[s][0] we dont make an edge between s and child
    dp[s][1] we make an edge between s and some child

    obv dp[s][0] is sum of max of childs
    dp[s][1] is we sum dp[v][1] assuming all taken, then pick best child
    s.t. dp[v][0] - dp[v][1] is maximum (best to connect with s).

    */
    cin >> n;
    adj.resize(n);
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(2);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, -1);
    cout << max(dp[0][0], dp[0][1]) << "\n";
}