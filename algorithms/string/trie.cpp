#include <bits/stdc++.h>

using namespace std;

const int K = 26;

struct vertex {
    int next[K];
    bool output = false;
    vertex() {
        for (int i = 0; i < K; i++)
            next[i] = -1;
    }
};

vector<vertex> trie(1);

// node itself doesnt have any value, only its reln with edges help
// so a vector with vertex pointing to next indices is fine,
// ordering is not needed anyway

void add_string(string const &s) {
    int v = 0; // root
    for (auto ch : s) {
        int c = ch - 'a';
        if (trie[v].next[c] == -1) {
            trie[v].next[c] = trie.size(); // new index point to
            trie.emplace_back();
        }
        v = trie[v].next[c];
    }
    trie[v].output = true;
}

bool search(const string &s) {
    int v = 0;

    for (auto ch : s) {
        int c = ch - 'a';
        if (trie[v].next[c] == -1)
            return false;
        v = trie[v].next[c];
    }
    if (trie[v].output == true)
        return true; // if want exact string presence, not prefix
}

int main() {}