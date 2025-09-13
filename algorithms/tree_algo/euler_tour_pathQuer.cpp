#include <bits/stdc++.h>

using namespace std;

/*
Euler tour with entry and exit times:
- Each node appears twice in flatten_tree (on entry and on exit).
- in[u], out[u] mark the positions.
- Subtree of u = [in[u], out[u]].
- Useful for path queries, difference updates (+X on entry, -X on exit).
- LCA(u,v) by using the traversed ancestors between [u...v] , since we store
node while exiting too (Range min query on depth)
- this approach used by cpalgo to get LCA.

for path queries, when we want to store +X when entering subtree
and -X while exiting... ie distinguish entry and exit times,
best to use tin, tout timer..

this distinguishes exit times of each node to different index,
so we can do point updates and do range queries
on subarray in[s] , out[s] for subtree of s
*/

vector<vector<int>> adj;
constexpr int N = 2e5 + 2;
vector<int> in, out;
vector<int> flatten_tree;
int tin = 0;

void dfs(int s, int p) {
    in[s] = tin++;
    flatten_tree.push_back(s);
    for (auto v : adj[s]) {
        if (v != p) {
            dfs(v, s);
        }
    }
    out[s] = tin++;
    flatten_tree.push_back(s); // store exiting ones also.
}

int main() {
    int n;
    cin >> n;
    in.resize(n);
    out.resize(n);
    adj.resize(n);

    /*
    take input of adj etc
    */

    dfs(0, -1);

    // now in flatten tree, in[s] and out[s] are ranges... exit times also
    // seperated
}