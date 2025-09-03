#include <bits/stdc++.h>
#define ll long long int

using namespace std;

ll n, m;

vector<bool> vis;

void dfs(ll s, vector<vector<ll>> &adj, vector<ll> &order) {
    vis[s] = true;
    for (auto &v : adj[s]) {
        if (!vis[v]) {
            dfs(v, adj, order);
        }
    }
    order.push_back(s);
}

pair<ll, ll> scc_rep(vector<vector<ll>> &adj) {

    vis.assign(n, false);
    vector<ll> order;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, adj, order);
        }
    }

    vector<vector<ll>> radj(n); // reverse edges, dfs on this to get components
    for (int i = 0; i < n; i++) {
        for (auto j : adj[i]) {
            radj[j].push_back(i);
        }
    }

    reverse(order.begin(), order.end()); // topo-ish sort
    vis.assign(n, false);
    int count = 1;
    vector<ll> component(n);
    for (auto v : order) {
        if (!vis[v]) {
            vector<ll> comp;
            dfs(v, radj, comp);
            for (auto &v : comp)
                component[v] = count;
            count++;
        }
    }

    // any two which are diff
    int s = component[0];
    for (int i = 1; i < n; i++) {
        if (component[i] > s) {
            return {i + 1, 1};
        } else if (s > component[i]) {
            return {1, i + 1};
        }
    }

    return {-1, -1};
}

int main() {
    cin >> n >> m;
    vector<vector<ll>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }
    pair<ll, ll> ans = scc_rep(adj);
    if (ans == make_pair(-1LL, -1LL)) {
        cout << "YES";
    } else {
        cout << "NO\n";
        cout << ans.first << " " << ans.second << "\n";
    }
}