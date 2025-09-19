#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int main() {
    /*
    WA do later

    */
    ll n, m;
    cin >> n >> m;
    vector<ll> adj[n];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }
    vector<ll> par(n, 0);
    par[0] = -1;
    vector<ll> dist(n, 0);
    dist[0] = 0;
    queue<ll> q;
    q.push(0);
    vector<bool> done(n, false);
    while (!q.empty()) {
        ll s = q.front();
        q.pop();
        for (auto &v : adj[s]) {
            if (done[v] == false) {
                q.push(v);
                done[v] = true;
            }
            if (dist[s] + 1 > dist[v]) {
                dist[v] = dist[s] + 1;
                par[v] = s;
            }
        }
    }
    vector<int> ans;
    int i = n - 1;
    while (par[i] != -1) {
        ans.push_back(i);
        i = par[i];
    }
    ans.push_back(0);
    cout << ans.size() << "\n";
    reverse(ans.begin(), ans.end());
    for (auto &x : ans)
        cout << 1 + x << " ";
}