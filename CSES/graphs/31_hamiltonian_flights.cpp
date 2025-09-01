#include <bits/stdc++.h>
#define ll long long int
using namespace std;

constexpr ll MAXN = 2e5 + 2;
constexpr ll mod = 1e9 + 7;

int max(int a, int b) { return (a > b ? a : b); }

ll dp[20][(1 << 20)];
/*
dp[i][mask]
number of ways to end at i,
with travelled the mask vertices.

dp[i][mask] += dp[k][mask^(kth bit)]
given kth bit of mask is set

also, k is ancestor of i, so
k->i given it travelled other vertices.

*/

void soln() {
    ll n, m;
    cin >> n >> m;
    vector<ll> adj[n];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[v].push_back(u); // ancestor graph
    }

    dp[0][1] = 1;

    for (ll mask = 3; mask < (1 << n); mask += 2) {
        for (ll k = 0; k < n; k++) {
            if ((mask >> k) & 1) {
                // end on k
                ll prev = mask ^ (1 << k);
                for (auto &v : adj[k]) {
                    // ancestor of k is v
                    if ((mask >> v) & 1) {
                        // if v in mask, add answer
                        dp[k][mask] += dp[v][prev];
                        dp[k][mask] %= mod;
                    }
                }
            }
        }
    }

    cout << dp[n - 1][((1 << n) - 1)];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    while (tt--) {
        soln();
    }
}