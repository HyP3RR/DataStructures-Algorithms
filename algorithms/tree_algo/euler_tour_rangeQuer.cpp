#include <bits/stdc++.h>

using namespace std;

/*
best way to flatten the tree is to use single entry timer
since timer only increase when we access it's child
so subtree is indexed for node a at index in[a],
[in[a]....in[a]+subtree_size[a]-1] this range is subtree of i... best for Range
based queries or approaches... but cannot distinguish entry and exit for leaf

*/

vector<vector<int>> adj;
constexpr int N = 2e5 + 2;
vector<int> flatten_tree;
vector<int> subtree_size;
vector<int> in;
int tin = 0;

void dfs(int s, int p) {

    in[s] = tin++; // indexing the nodes
    subtree_size[s] = 1;
    flatten_tree.push_back(s); // order traversal
    for (auto v : adj[s]) {
        if (v != p) {
            dfs(v, s);
            subtree_size[s] += subtree_size[v];
        }
    }
}

int main() {
    int n;
    cin >> n;
    in.resize(n);
    adj.resize(n);
    subtree_size.resize(n);
    /*
    take adj input
    */
    dfs(0, -1);
    // for any node u at index in[u] , in[u] + subtree_size[u]-1 is the range
}