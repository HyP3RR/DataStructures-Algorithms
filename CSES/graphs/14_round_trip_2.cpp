#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> done;
int last = -1;
deque<int> ans;
void dfs(int s) {
    done[s] = 1;
    ans.push_back(s);
    done[s] = true;
    for (auto &v : adj[s]) {
        if (done[v] == 0)
            dfs(v);
        else if (done[v] == 1) {
            // back edge, if root still being processed.

            ans.push_back(v);
            while (*ans.begin() != v)
                ans.pop_front();
            last = 1;
            return;
        }
        if (last != -1)
            return;
    }
    done[s] = 2;
    ans.pop_back();
}

int main() {
    /*
    since directed graph use in out,
    if backedge if s node still being procesed

    so direct logic to push and pop after processing,
    so ans always contain current path
    */
    cin >> n >> m;
    adj.resize(n);
    done.resize(n, false);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }
    for (int i = 0; i < n; i++) {
        if (done[i] == 0 && last == -1)
            dfs(i); // vis all and if only no answer
    }
    if (last == -1) {
        cout << "IMPOSSIBLE \n";
    } else {
        cout << ans.size() << '\n';
        for (auto &v : ans)
            cout << v + 1 << " ";
        cout << "\n";
    }
}