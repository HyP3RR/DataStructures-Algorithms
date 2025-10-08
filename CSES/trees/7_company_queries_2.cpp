#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 1;
vector<int> dep;
int jmp[MAXN][30];
vector<vector<int>> adj;

void dfs(int s, int p, int d) {
    dep[s] = d;
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
        int p;
        cin >> p;
        p--;
        jmp[i][0] = p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }
    for (int i = 1; i < 30; i++) {
        for (int node = 0; node < n; node++) {
            if (jmp[node][i - 1] != -1)
                jmp[node][i] = jmp[jmp[node][i - 1]][i - 1];
        }
    }
    dfs(0, -1, 0);
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        if (dep[a] > dep[b])
            a = up(a, dep[a] - dep[b]);
        else
            b = up(b, dep[b] - dep[a]);

        // same level now
        int v = LCA(a, b);
        cout << v + 1 << "\n";
    }
}