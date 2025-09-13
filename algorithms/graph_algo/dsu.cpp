#include <bits/stdc++.h>
#define ll long long int
using namespace std;

vector<ll> parent(1e5 + 2);
vector<ll> set_size(1e5 + 2);

void make_set(int node) {
    parent[node] = node;
    set_size[node] = 1;
}

ll find_representative(ll node) {
    if (parent[node] == node)
        return node;
    return parent[node] = find_representative(parent[node]);
    // this does path compressions!
    // connects all node in the path to root(representative)
    // by directly linking it to root! O(1) access next time
}

void union_set(ll node1, ll node2) {
    node1 = find_representative(node1);
    node2 = find_representative(node2);
    if (node1 != node2) { // check for same representative
        if (set_size[node1] > set_size[node2])
            swap(node1, node2);
        // now node2 size > node1 size set
        // join node1 to node2 as representative
        parent[node1] = node2;
        set_size[node2] += set_size[node1];
        //this keeps tree size overall limited
    }
}

int main() {

    
}