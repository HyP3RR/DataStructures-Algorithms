#include <bits/stdc++.h>

using namespace std;

/*
best way to flatten the tree is to use single entry timer
since timer only increase when we access it's child
so subtree is indexed for node i, [i....tout[i]+i]
this range is subtree of i...
best for Range based queries or approaches... but cannot distinguish
entry and exit for leaf

for path queries, when we want to store +X when entering subtree
and -X while exiting... ie distinguish entry and exit times,
best to use tin+tout timer,  ie increment in both cases...
*/

vector<vector<int>> adj;
constexpr int N = 2e5 + 2;
vector<int> flatten_tree;
vector<int> subtree_size;
int tin = 0;

void dfs(int s, int p) {
    flatten_tree.push_back(s);
    for (auto v : adj[s]) {
        if (v != p)
            dfs(v, s);
    }
}

int main() {
    int n;
    cin >> n;
    adj.resize(n);
    subtree_size.resize(n);
}