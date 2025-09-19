#include <bits/stdc++.h>
#define ll long long int

using namespace std;

struct node {
    ll min_price = 1e17;
    ll routes = 0;
    ll min_flights = 1e9;
    ll max_flights = 0;
};

const ll mod = 1e9 + 7;
int main() {
    /*
    direct dijikstra, we maintain extra info in vector of nodes
    only push if < v, since the if a node v has equal dist[s] + w, it'll
    definitely be processed later as s has lesser dist than v... so no need for
    double push
    */
    int n, m;
    cin >> n >> m;
    vector<pair<ll, ll>> adj[n];
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
    }
    vector<ll> dist(n, 1e17);
    vector<ll> routes(n, 0);
    dist[0] = 0;

    vector<node> info(n);
    info[0].min_price = 0;
    info[0].routes = 1;
    info[0].min_flights = 0;
    info[0].max_flights = 0;
    priority_queue<pair<ll, ll>> pq; // store -ve dist so least dist on top
    pq.push({0, 0});
    // fuckk there are parallel edges
    while (!pq.empty()) {
        ll cur_dist = -pq.top().first;
        ll s = pq.top().second;
        pq.pop();
        if (cur_dist > dist[s])
            continue; // for parallel edges, we might push twice due to double
                      // relaxations while iterating over (s,v)
        // if out-dated push, we check here
        for (auto &p : adj[s]) {
            ll w = p.second;
            ll v = p.first;
            if (dist[s] + w < dist[v]) {
                dist[v] = dist[s] + w;
                info[v] = {dist[v], info[s].routes, info[s].min_flights + 1,
                           info[s].max_flights + 1};
                pq.push({-dist[v], v});
            } else if (dist[s] + w == dist[v]) {
                info[v].routes += info[s].routes;
                info[v].routes %= mod;
                info[v].min_flights =
                    min(info[v].min_flights, info[s].min_flights + 1);
                info[v].max_flights =
                    max(info[v].max_flights, info[s].max_flights + 1);
            }
        }
    }
    cout << info[n - 1].min_price << " " << info[n - 1].routes << " "
         << info[n - 1].min_flights << " " << info[n - 1].max_flights << "\n";
}