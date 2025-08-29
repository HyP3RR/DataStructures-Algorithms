#include <bits/stdc++.h>
#define ll long long int
using namespace std;

constexpr ll MAXN = 2e5 + 2;

/*
Kosaraju's Algorithm:
find SCC in O(n+m)
*/
struct Kosaraju {
  private:
    vector<vector<int>> adj;
    vector<bool> vis;
    int n;

    void dfs(int s, vector<vector<int>> &adj, vector<int> &order) {
        // qualified lookup binds to adj!
        vis[s] = true;
        for (auto &v : adj[s]) {
            if (vis[v] != true) {
                dfs(v, adj, order);
            }
        }
        order.push_back(s);
        /*
        (reverse later)
        after reverse order is in
        ascending order of tout!

        we know tout Ci > tout Cj if Ci->Cj
        where Ci and Cj are SCC.

        note-
        tout Ci -> max tout v in Ci
        tin Ci => min tin v  in ci.
        */
    }

  public:
    /*
    user passes in vector to add each SCC components
    components -> list of components
    adj_cond -> condensation graph (adj list with each
    SCC collapsed into single vertex)
    */
    void generate_scc(vector<vector<int>> &components,
                      vector<vector<int>> &adj_cond) {
        components.clear();
        adj_cond.clear();

        vis.assign(n, false);

        vector<int> order;

        // series of dfs to get topo-ish sort
        for (int i = 0; i < n; i++) {
            if (!vis[i])
                dfs(i, adj, order);
        }

        reverse(order.begin(), order.end());
        /*
        how does it work internally?

        must have a bidirectional iterator
        last is past-the-end iter -> careful
        shortcircuit by checking if same,
        and dec last check

        vector have random access iterator which
        are stronger than bidirectional ones -> hence work

        template<typename BidirectionalIterator>
        void reverse(BidirectionalIterator first, Bidirectional last){
        while((first != last) && (first != --last)){
        std::iter_swap(first, last);
        first++;
        }
        }

        to make your own iterator, need to include iterator traits
        (by 'using' keyword) to make it compatible to stl.
        As reverse etc stl function check for iterator traits.
        */

        // create G^T (reversed graph)
        vector<vector<int>> adj_rev(n);
        for (int i = 0; i < n; i++) {
            for (auto &v : adj[i]) {
                adj_rev[v].push_back(i);
            }
        }

        // in order of toposort, do dfs
        // on this G^T to get list of components
        vis.assign(n, false);
        vector<int> component;

        vector<int> roots(n, 0); // give root vertex of SCC (representative)

        for (auto &v : order) {
            if (!vis[v]) {
                dfs(v, adj_rev, component);
                components.push_back(component);
                int root = *min_element(component.begin(), component.end());
                component.clear();
                for (auto u : component)
                    roots[u] = root;
                // for condensation graph (if needed)
            }
        }

        adj_cond.assign(n, {});
        // order is in order of topo-ish sort
        // so, for original edge u->v
        // if roots not equal root(u) -> root(v)
        // also, since if they lie in diff SCC
        // SCC(u)->SCC(v) because u->v
        for (int u = 0; u < n; u++) {
            for (auto v : adj[u]) {
                if (roots[u] != roots[v]) {
                    adj_cond[roots[u]].push_back(roots[v]);
                }
            }
        }
    }

    Kosaraju(vector<vector<int>> adj) {
        this->n = adj.size();
        swap(adj, this->adj);
        vis.assign(n, false);
        // sets size to n and is assigned false
    }
};

void soln() {}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    while (tt--) {
        soln();
    }
}