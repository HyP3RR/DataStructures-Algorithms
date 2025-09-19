#include <bits/stdc++.h>
#define ll long long int

using namespace std;
const ll mod = 1e9 + 7;
int main() {
    /*
    DAG DP best
    use toposort method and
    for edge u,v do val[v] += val[s]
    and pick next to be one with no parent (ie no pending routes to count) for
    the node
    */
    ll n, m;
    cin >> n >> m;
    vector<ll> adj[n];
    vector<ll> par(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        par[v]++;
    }
    vector<ll> ways(n, 0);
    ways[0] = 1;
    queue<ll> q;
    for (int i = 0; i < n; i++) {
        if (par[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {
        int s = q.front();
        q.pop();
        for (auto &v : adj[s]) {
            ways[v] += ways[s];
            ways[v] %= mod;
            par[v]--;
            if (par[v] == 0)
                q.push(v);
        }
    }
    cout << ways[n - 1] << "\n";
}