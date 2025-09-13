#include <bits/stdc++.h>
#define ll long long int
using namespace std;

vector<ll> telep(2e5 + 2);
vector<bool> vis(2e5 + 2, false);
ll n;
vector<ll> succ(2e5 + 2);

void dfs(int s, vector<ll> &path) {
    path.push_back(s);
    if (vis[s] == true) {
        return;
    }
    vis[s] = true;
    dfs(succ[s], path);
}

int main() {
    /*
    just run DFS , make path vector
    two cases if we run into a cycle on this path
    or we reach an already processed node..
    handle and mark visited.
    */
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> succ[i];
        succ[i]--;
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            vector<ll> path;
            dfs(i, path);
            int sz = path.size();
            int ind_cycle = -1;
            for (int i = 0; i < sz - 1; i++) {
                if (path[i] == path[sz - 1]) {
                    // we re-traced
                    ind_cycle = i;
                    break;
                }
            }
            if (ind_cycle == -1) {
                // we reached a processed node
                for (int i = 0; i < sz - 1; i++) {
                    telep[path[i]] = telep[path[sz - 1]] + (sz - 1 - i);
                }
            } else {
                // re-visited our cycle
                for (int i = ind_cycle; i < sz; i++) {
                    telep[path[i]] = (sz - 1 - ind_cycle); // fixed cycle
                }
                for (int i = ind_cycle - 1; i >= 0; i--) {
                    telep[path[i]] = telep[path[i + 1]] + 1; //add contribution of this node.
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << telep[i] << " ";
    }
}