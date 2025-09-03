#include <bits/stdc++.h>
#define ll long long int

using namespace std;

ll n, m;
ll tout = 0;
vector<ll> vis(1e5 + 1, false);

void dfs(ll s, vector<vector<ll>> &adj, vector<ll> &order) {
    vis[s] = true;
    for (auto &v : adj[s]) {
        if (vis[v] != true) {
            dfs(v, adj, order);
        }
    }
    order.push_back(s);
}

vector<vector<ll>> scc(vector<vector<ll>> &adj, vector<ll> &w) {

    // sort nodes in descending order of tout
    vector<ll> order;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, adj, order);
        }
    }

    tout = 0;
    vis.assign(n, false); // reset global states

    reverse(order.begin(), order.end());
    // now it is 'somewhat' toposort.

    // reverse all edges, then dfs on it to get each component
    // this is equivalent to ordering nodes in their SCC DAG, then reverse edges
    // of SCC dag so no node will 'escape' its component of SCC. intuition is
    // toposort and SCC dag
    vector<vector<ll>> radj(n);
    for (int i = 0; i < n; i++) {
        for (auto &v : adj[i]) {
            radj[v].push_back(i);
        }
    }
    // dfs in order of 'order' on reversed edges, each new component is SCC
    // represent SCC graph by min node value in it

    /*
    to make scc graph:
    we find scc in toposorted order, so number all nodes inside by 1,2... (call
    toponum) then by original edges, if adjacent nodes have diff toponum, the
    scc graph has this edge connect the representative nodes
    */

    vector<ll> toponum(n, 0); // this is also representative
    ll cnt = 0;
    vector<ll> fin(n, 0);
    for (int i = 0; i < order.size(); i++) {
        int nd = order[i];
        if (!vis[nd]) {
            vector<ll> comp;
            ll sum = 0;
            dfs(nd, radj, comp);
            ll mini = n;
            for (auto &v : comp) {
                toponum[v] = cnt;
                sum += w[v];
            }
            fin[cnt] = sum;
            cnt++;
        }
    }

    vector<set<ll>> scc_g(cnt); // toponum 0..cnt-1
    // construct scc graph
    for (int i = 0; i < n; i++) {
        for (auto &v : adj[i]) {
            if (toponum[i] != toponum[v]) {
                // edge lesser to inc toponum
                if (toponum[i] < toponum[v]) {
                    // i -> v
                    scc_g[toponum[i]].insert(toponum[v]);
                } else {
                    // v -> i
                    scc_g[toponum[v]].insert(toponum[i]);
                }
            }
            // using set as some edges can repeat!!
            //(eg. 0->1 1->2 2->1 0->2)... 0->1 0->1 occurs twice!
        }
    }
    w = fin;
    vector<vector<ll>> ans(cnt);
    for (int i = 0; i < scc_g.size(); i++)
        for (auto &v : scc_g[i])
            ans[i].push_back(v);
    return ans;
}

ll dag_sum(vector<vector<ll>> &adj, vector<ll> &a) {
    int n = adj.size();
    a.resize(n);
    vector<ll> dp(a.begin(), a.end());
    vector<ll> topo_sort;
    vis.assign(n, false);
    tout = 0;

    // dp on dag! instead of dijikstra!
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, adj, topo_sort);
        }
    }
    reverse(topo_sort.begin(), topo_sort.end());
    for (int i = 0; i < n; i++) {
        int cur = topo_sort[i];
        for (auto &v : adj[cur]) {
            dp[v] = max(dp[v], dp[cur] + a[v]);
        }
    }
    return *max_element(dp.begin(), dp.end());
}

int main() {
    cin >> n >> m;
    vector<ll> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    vector<vector<ll>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }

    vector<vector<ll>> nadj = scc(adj, v);

    ll ans = dag_sum(nadj, v);

    cout << ans;
}