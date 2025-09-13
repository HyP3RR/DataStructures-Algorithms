#include <bits/stdc++.h>
#define ll long long int
using namespace std;

constexpr ll MAXN = 2e5 + 2;
constexpr ll mod = 1e9 + 7;

int max(int a, int b) { return (a > b ? a : b); }

ll dp[MAXN][2];
vector<ll> adj[MAXN];
vector<ll> ans(MAXN);
ll n;
void dfs(int s, int p) {

    for (auto &v : adj[s]) {
        if (v != p) {
            dfs(v, s);
            dp[s][0] += dp[v][0] + dp[v][1];
            dp[s][1] += dp[v][1]; // no. of nodes in subtree
        }
    }
}

void dfs2(int s, int p) {

    for (auto &v : adj[s]) {
        if (v != p) {
            ans[v] = ans[s] + n - 2 * dp[v][1];
            dfs2(v, s);
        }
    }
}

void soln() {

    /*
    approach:
    dp[i][0] is sum of all dist in subtree i
    dp[i][1] is number of nodes in subtree of i

    first dfs is basically getting initial answers
    mostly for root!

    dfs2 implements a re-rooting technique
    basically if root is S and we go to V
    ans[V] = ans[S] - subtree(nodes V) + (n-Subtreenodes(V))
    basically subtree(nodes v) got closer by 1 edge
    and N-Subtree(node v) got farther by 1 edge!

    implementation is a bit roundabout

    */
    cin >> n;

    for (int i = 0; i < n; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
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

    for (int i = 0; i < n; i++)
        ans[i] = dp[i][0];
    dfs2(0, -1);
    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    while (tt--) {
        soln();
    }
}