#include <bits/stdc++.h>
#define ll long long int
using namespace std;

class DSU {
    static constexpr int n =
        1e5 + 2; // static constexpr can be initialised inside.
    vector<ll> par;
    vector<ll> sz;

  public:
    DSU() : par(n), sz(n) {
        for (int i = 0; i < n; i++) {
            par[i] = i;
            sz[i] = 0;
        }
    }

    int find_rep(int s) {
        if (par[s] == s)
            return s;
        return par[s] = find_rep(par[s]);
    }

    void union_set(int u, int v) {
        u = find_rep(u);
        v = find_rep(v);
        if (u != v) {
            if (sz[u] > sz[v])
                swap(u, v);
            // sz[v] > sz[u]
            par[u] = v;
            sz[v] += sz[u];
        }
    }
};

int main() {
    /*
    basic spanning tree form , connect edge
    in order of inc construction cost, if they lie
    in same component, don't.

    use DSU for checking representative, and
    incrementally take union!
    */
    int n, m;
    cin >> n >> m;
    DSU dsu{}; // take care not to make it most vexing parse
    vector<std::array<int, 3>> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    sort(a.begin(), a.end(),
         [](const std::array<int, 3> &a, const std::array<int, 3> &b) {
             return b[2] > a[2];
         });
    ll ans = 0;
    for (auto edge : a) {
        int u = edge[0];
        int v = edge[1];
        if (dsu.find_rep(u) != dsu.find_rep(v)) {
            dsu.union_set(u, v);
            ans += edge[2];
        }
    }
    int rep = dsu.find_rep(1);

    for (int i = 1; i <= n; i++) {
        if (rep != dsu.find_rep(i)) {
            cout << "IMPOSSIBLE \n";
            return 0;
        }
    }
    cout << ans << "\n";
}