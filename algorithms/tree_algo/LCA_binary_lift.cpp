#include <bits/stdc++.h>

using namespace std;

/*
LCA by binary lifting, two cases:
1. node a, b same depth -> find min val = k, s.t. kth ancestor same.
we can do this easily, start j from max set bit:
-> if same ancestor, do nothing
-> if different, we update a and b to their 2^jth ancestors...

    this works, if LCA is 10100(K) away -> we never mark 0 bit because they will
overshoot we always mark 1 wale bit (except the last 1), because they are lesser
than K so we get 10011 and we add 1 by doing up[a][0] , and we get exactly the
LCA.


2. diff depth -> convert to same depth, by jumping (ha-hb) of the deeper node.
    if same vertex -> answer.. now case 1.
*/

// application: dist(a,b) = depth(a) + depth(b) - 2*depth(LCA(a,b))

constexpr int N = 2e5 + 2;
vector<vector<int>> adj(N);
int n;
vector<int> depth(N);
int up[N][20];

void dfs(int s, int par, int d) {
    up[s][0] = par;
    depth[s] = d;
    for (auto v : adj[s]) {
        if (v != par)
            dfs(v, s, d + 1);
    }
}

int lift(int node, int dist) {
    int final_node = node;
    for (int j = 19; j >= 0; j--) {
        if (dist & (1 << j) && final_node != -1) {
            // bit j is set
            final_node = up[final_node][j];
        }
    }
    return final_node;
}

int lca(int a, int b) {
    int pa = lift(
        a, depth[a] -
               min(depth[a], depth[b])); // either 0 or +ve for the lifting one
    int pb = lift(b, depth[b] - min(depth[a], depth[b]));
    a = pa; // prevent overwriting while calling lift in b.
    b = pb;
    if (a == b)
        return a;
    else {
        // now find minimum value k , s.t. both have same ancestor
        // idea explained above
        for (int j = 19; j >= 0; j--) {
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }
        return up[a][0];
    }
}

int main() {

    cin >> n;
    adj.resize(n);
    /*
    fill adj n-1 edges
    */
    memset(up, -1, sizeof(up));
    dfs(0, -1, 0);
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i < n; i++) {
            if (up[i][j - 1] != -1)
                up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    int a, b;
    cin >> a >> b;
    a--;
    b--;
    int ans = lca(a, b);
}