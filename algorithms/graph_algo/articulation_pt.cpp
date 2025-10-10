#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<int> low;
vector<int> st;
int tin = 0;
vector<bool> done;

vector<int> articulation_pt;

/*
things i missed:
1. checking for root node, needs special handling
2. s,v weird confusion.
3. could have duplicates in vector.

**only works for undirected graphs as explained in comments.
*/

void dfs(int s, int p) {
    done[s] = true;
    low[s] = st[s] = tin++;
    //
    int child = 0;
    for (auto &v : adj[s]) {
        if (v == p)
            continue; // back to parent edge doesnt affect ap
        if (done[v] == true) {
            low[s] = min(low[s], st[v]);
        } else {
            dfs(v, s);
            low[s] = min(low[v], low[s]);
            if (low[v] >= st[s] && p != -1)
                articulation_pt.push_back(
                    s); //(s,v) subtree v stays within s (and no cross edge!)
            // so for any s,v case, we can remove s and v wala subtree is
            // disconnected now! this wont work if v has cross edges and st[v']
            // > st[s] but v' could have low above s! think about that case
            child++;
        }
    }
    if (p == -1 && child > 1)
        articulation_pt.push_back(s); // extra handling for root node, low[s]
}

int main() {
    int n;
    cin >> n;
    adj.resize(n);
    low.resize(n, 1e8);
    st.resize(n);
    done.resize(n, false);
}