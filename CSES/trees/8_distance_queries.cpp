#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 1;
vector<int> dep;
int jmp[MAXN][30];
vector<vector<int>> adj;

void dfs(int s, int p, int d) {
    dep[s] = d;
    jmp[s][0] = p;
    for (auto &v : adj[s]) {
        if (v != p)
            dfs(v, s, d + 1);
    }
}

int up(int s, int k) {

    int ans = s;
    for (int i = 0; i < 30; i++) {
        int v = ((k >> i) & 1);
        if (v && ans != -1)
            ans = jmp[ans][i];
    }
    return ans;
}

int LCA(int a, int b) {
    if (a == b)
        return a;
    for (int i = 29; i >= 0; i--) {
        if (jmp[a][i] != jmp[b][i]) {
            a = jmp[a][i];
            b = jmp[b][i];
        }
    }
    return jmp[a][0];
}

int main() {
    int n, q;
    cin >> n >> q;
    dep.resize(n);
    adj.resize(n);
    memset(jmp, -1, sizeof(jmp));
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, -1, 0);
    for (int i = 1; i < 30; i++) {
        for (int node = 0; node < n; node++) {
            if (jmp[node][i - 1] != -1)
                jmp[node][i] = jmp[jmp[node][i - 1]][i - 1];
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int u, v;
        u = a;
        v = b;
        if (dep[u] > dep[v])
            u = up(u, dep[u] - dep[v]);
        else
            v = up(v, dep[v] - dep[u]);
        // same level now

        int lca = LCA(u, v);
        cout << dep[a] + dep[b] - 2 * dep[lca] << "\n";
    }
}