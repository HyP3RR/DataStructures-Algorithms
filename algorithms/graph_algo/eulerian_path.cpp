#include <bits/stdc++.h>

using namespace std;

vector<int> euler_cycle(vector<vector<int>> &adj_org, int n, int m) {
    /*
    necessary and suff condn -> deg(vi)%2 == 0 and connected for all vi!

    start from i, keep going,
    when you loop back and no-where to go, merge the vertices in cycle
    and remove the edges...
    now, considering this whole merge vertex,
    again continue finding new paths (ie from any vertex
    involved in the cycle)
    this is simulated via stack and pop to check degree of intermediate nodes in
    b/w

    push the path in reverse order (when deg = 0), as if it missed some
    cycle, it'll go back and re-traverse it. so we are forming path in opposite
    traversal!

    for directed graph case, we are traversing reverted edges!(so need to
    reverse it again) no need for normal edges tho

    impl: stack! delete edges as you traverse, if no where to go, pop that
    vertex and go back to check if we missed some cycle. path in order of
    popping is correct


    CP algo does it in O(M) and O(n^2) memory, need to do better
    */

    // necessity check incoming = outgoing edges
    vector<int> in(n);
    vector<int> out(n);
    for (int i = 0; i < n; i++) {
        for (auto &v : adj_org[i]) {
            in[v]++;
            out[i]++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (in[i] != out[i])
            return {};
    }

    // FIX TLE BY USING multiset (edge (n,1) can introduce parallel edges)
    vector<multiset<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (auto &v : adj_org[i]) {
            adj[i].insert(v);
            // we remove edge as we traverse.
        }
    }

    stack<int> cycle;
    vector<int> path;
    cycle.push(0);
    while (!cycle.empty()) {
        int s = cycle.top();
        bool deg = false;

        if (!adj[s].empty()) { // erase edge if traversing
            cycle.push(*adj[s].begin());

            adj[s].erase(adj[s].begin());
        } else { // form path in opposite order! find more paths by popping the
                 // cycles formed
            // and checkking for new edges for a node.
            path.push_back(s);
            cycle.pop();
        }
    }
    // sanity check, if all edges (or deg) = 0
    // hence graph is connected also
    for (int i = 0; i < n; i++) {
        if (!adj[i].empty())
            return {};
    }
    reverse(path.begin(),
            path.end()); // actual tour, although need to fix if euler path!

    // NOW EXTRA PROCESSING TO GET PATH 1->N
    // find first pair (n,1)... ensure that must be last now
    // sequence [1....N,1] re-place at end
    // ignore [n,1] so we get answer!
    vector<int> answer;
    for (int i = 0; i + 1 < path.size(); i++) {
        if (path[i] == n - 1 && path[i + 1] == 0) {
            int ind1 = -1;
            for (int j = i; j >= 0; j--) {
                if (path[j] == 0) {
                    ind1 = j;
                    break;
                }
            }

            for (int k = 0; k < ind1; k++)
                answer.push_back(path[k]); //[1....X,1....N,1.....Y,1]
            for (int k = i + 1; k < path.size(); k++)
                answer.push_back(path[k]);
            // last mein always 1, so we ignore ind1
            for (int k = ind1 + 1; k <= i; k++)
                answer.push_back(path[k]);
            // finally [1.....X,1....Y,1.....N] (extra 1 gone)
            break;
        }
    }
    return answer;
}

int main() {
    /*
    eulerian path from 1->n , is just finding
    eulerian cycle 1->1 if we add an edge n->1.
    hier-holzer algorithm

    it is teleporters path from cses, check it out.
    */
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }
    adj[n - 1].push_back(0); // euler cycle conversion
    vector<int> path = euler_cycle(adj, n, m);
    if (path.empty())
        cout << "IMPOSSIBLE";
    else {

        for (auto &x : path) {
            cout << x + 1 << " ";
        }
    }
}