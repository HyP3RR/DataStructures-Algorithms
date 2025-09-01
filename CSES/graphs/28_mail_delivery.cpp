#include <bits/stdc++.h>

using namespace std;

vector<int> euler_tour(vector<vector<int>> &adj_org, int n, int m) {

    for (int i = 0; i < n; i++) {
        if (adj_org[i].size() % 2 == 1)
            return {};
    }

    vector<multiset<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (auto &v : adj_org[i]) {
            adj[i].insert(v);
        }
    }

    stack<int> s;
    s.push(0);
    vector<int> path;
    while (!s.empty()) {
        int cur = s.top();
        if (!adj[cur].empty()) {
            s.push(*adj[cur].begin());
            int u = cur, v = *adj[cur].begin();
            adj[cur].erase(adj[cur].begin());
            adj[v].erase(u); // erase both sides

        } else {
            path.push_back(cur);
            s.pop();
        }
    }

    // sanity check, for connectedness
    for (int i = 0; i < n; i++) {
        if (!adj[i].empty())
            return {};
    }
    // no handling since no euler path, only cycle

    return path;
}

int main() {
    // basic euler tour, not even extra processing
    // undirected graph
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> path = euler_tour(adj, n, m);
    if (!path.empty()) {
        for (auto &v : path)
            cout << v + 1 << " ";
    } else {
        cout << "IMPOSSIBLE";
    }
}