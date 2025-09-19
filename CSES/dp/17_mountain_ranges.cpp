#include <bits/stdc++.h>
#define ll long long int
using namespace std;
ll n;
vector<ll> a;
vector<vector<ll>> adj;

void nextg() {
    stack<pair<ll, ll>> nge;
    for (int i = 0; i < n; i++) {
        while (nge.size() > 0 && a[i] > nge.top().first) {
            adj[i].push_back(nge.top().second); // dep graph
            nge.pop();
        }
        nge.push({a[i], i});
    }
    while (nge.size())
        nge.pop();
    for (int i = n - 1; i >= 0; i--) {
        while (nge.size() > 0 && a[i] > nge.top().first) {
            adj[i].push_back(nge.top().second); // dep graph
            nge.pop();
        }
        nge.push({a[i], i});
    }
}

int main() {
    /*
    idea, we always start from max element and go to maximum element just
    smaller than current.. this is equivalent to say we always move from next
    greater element to current element. by next greater element of lhs and rhs,
    we give only the best possibilities to the element which is nge of
    someone... since all indices in between will be lesser (otherwise current
    element wont be nge)

    now, by making a graph from the element which is nge of someone  -> ind of
    lesser one we can use toposort logic to process and find best answer in
    ending_ans(i)
    */
    cin >> n;
    a.resize(n);
    adj.resize(n);

    for (auto &x : a)
        cin >> x;
    nextg();
    vector<ll> par(n, 0);
    for (int i = 0; i < n; i++) {
        for (auto v : adj[i]) {
            par[v]++;
        }
    }
    vector<ll> ending_ans(n, 1); // best ans if ending on index i
    queue<ll> topo;
    for (int i = 0; i < n; i++) {
        if (par[i] == 0)
            topo.push(i);
    }
    while (!topo.empty()) {
        int ind = topo.front();
        topo.pop();
        for (auto v : adj[ind]) {
            ending_ans[v] = max(ending_ans[v], ending_ans[ind] + 1);
            par[v]--;
            if (par[v] == 0)
                topo.push(v);
        }
    }
    cout << *max_element(ending_ans.begin(), ending_ans.end());
}