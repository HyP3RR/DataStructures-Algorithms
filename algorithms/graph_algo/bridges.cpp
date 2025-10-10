#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<int> low;
vector<int> st;
int tin = 0;
vector<bool> done;

vector<pair<int, int>> bridges;

/*
things i missed:
1. parallel edges check via parents skipped

also for undirected graph! think about intrinsic handling for digraphs!
*/

void dfs(int s, int p) {
    low[s] = st[s] = tin++;
    done[s] = true;
    bool parent_skipped = false; // only skip once! to account for parallel
                                 // edges
    for (auto &v : adj[s]) {
        if (v == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (done[v]) {
            low[s] = min(st[v], low[s]);
        } else {
            dfs(v, s);
            low[s] = min(low[v], low[s]);
            if (low[v] > st[s])
                bridges.push_back({s, v});
        }
    }
}

int main() {
    int n;
    cin >> n;
    adj.resize(n);
    low.resize(n, 1e8);
    st.resize(n);
    done.resize(n, false);
}