#include <bits/stdc++.h>
#define ll long long int

using namespace std;

constexpr ll N = 2e5 + 2;

vector<ll> t(4 * N); // v is one indexed, tl..tr is 0..n-1
vector<ll> a(N);

ll min(ll x, ll y) { return (x > y ? y : x); }
ll max(ll x, ll y) { return (x > y ? x : y); }

void make(ll v, ll tl, ll tr) {
    if (tl == tr)
        t[v] = a[tl];
    else {
        ll tm = (tl + tr) >> 1;
        make(2 * v, tl, tm);
        make(2 * v + 1, tm + 1, tr);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
}

ll query(ll v, ll tl, ll tr, ll l, ll r) {
    if (tl == l && tr == r)
        return t[v];
    if (l > r)
        return LLONG_MAX;
    ll tm = (tl + tr) >> 1;
    return min(query(2 * v, tl, tm, l, min(r, tm)),
               query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
}

int main() {
    /*
    to find max subarr sum of length between A,B
    i made prefix sum and found minimum prefix to subtrack
    which is between index i-B,i-A...
    we can do this by maintaining a multiset of values and updating
    it as we move the index.
    I did it by segtree.
    */
    ll n;
    cin >> n;
    ll A, b;
    cin >> A >> b;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        a[i] += a[i - 1];
    make(1, 0, n);
    ll maxi = -LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        int l = i - b;
        int r = i - A;
        l = max(l, 0);
        if (l <= r) {
            maxi = max(maxi, a[i] - query(1, 0, n, l, r));
        }
    }
    cout << maxi << "\n";
}
