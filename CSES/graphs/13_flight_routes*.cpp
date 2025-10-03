#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
    /*
    maintain dist priority queue for best k distance estimates
    dijikstra but we do it for the largest valid estimate (if changed)

    my problem with vector was i couldnt track the lower val one which had been
    processed already, so by doing it via priority queue, it can be tracked when
    an estimate is updated


    */
    ll n, m, k;
    cin >> n >> m >> k;
    vector<pair<ll, ll>> adj[n];
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
    }
    priority_queue<ll> dist[n];
    priority_queue<pair<ll, ll>> pq;
    pq.push({0, 0});
    dist[0].push(0);
    while (!pq.empty()) {
        ll s = pq.top().second;
        ll di = -pq.top().first;
        pq.pop();
        if (di > dist[s].top())
            continue; // prune for those v s.t. it's best estimate is greater
                      // than dist[v] max already
        for (auto &p : adj[s]) {
            ll v = p.first;
            ll w = p.second;
            if (dist[v].size() < k) {
                dist[v].push(w + di);
                pq.push({-w - di, v});
            } else if (dist[v].top() > di + w) {
                dist[v].pop();
                dist[v].push(di + w);
                pq.push({-di - w, v});
            }
        }
    }
    vector<ll> ans;
    while (!dist[n - 1].empty()) {
        ans.push_back(dist[n - 1].top());
        dist[n - 1].pop();
    }
    reverse(ans.begin(), ans.end());
    for (auto &x : ans)
        cout << x << " ";
}