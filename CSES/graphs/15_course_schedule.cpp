#include <bits/stdc++.h>
#define ll long long int

using namespace std;

ll n, m;
vector<vector<ll>> adj;
vector<int> done;
vector<int> ans;
int no_ans;
void dfs(int s) {
    done[s] = 1;
    for (auto &v : adj[s]) {
        if (done[v] == 0) {
            dfs(v);
        } else {
            if (done[v] == 1) {
                // back edge
                no_ans = -1;
            }
        }
    }
    done[s] = 2;
    ans.push_back(s);
}

int main() {
    /*
    toposort dfs method,
    backedge while node v is being  processec -> cycle
    if it has been processed, that means we had started from descendent so no
    issue we push in order of latest exit, so the last courses are first, so we
    reverse it.


    */
    cin >> n >> m;
    adj.resize(n);
    done.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }

    for (int i = 0; i < n; i++) {
        if (done[i] == 0)
            dfs(i);
    }
    reverse(ans.begin(), ans.end());
    if (no_ans == -1) {
        cout << "IMPOSSIBLE";
    } else {
        for (auto &v : ans)
            cout << v + 1 << " ";
    }
}