#include <bits/stdc++.h>
#define ll long long int
using namespace std;

constexpr ll MAXN = 2e5 + 2;

constexpr ll mod = 1e9 + 7;

struct node {
    ll val;
};

struct SegmentTree {

  private:
    ll n;
    vector<node> t;

    void build(const vector<ll> &a, ll v, ll tl, ll tr) {
        // t[v] = node, we use 2*v, 2*v+1 as child of v. (tree sim)
        // usng 0 based indexing
        if (tl == tr) {
            t[v].val = a[tl]; //[5,5] thus a[5]
        } else {
            ll tm = (tl + tr) >> 1;
            build(a, 2 * v, tl, tm);
            build(a, 2 * v + 1, tm + 1, tr);
            t[v].val = t[2 * v].val + t[2 * v + 1].val;
        }
    }

    ll query(ll v, ll tl, ll tr, ll l, ll r) const {
        if (l > r) {
            // return default value, which
            // does not affect the binary operator
            // which we are checking for
            return 0;
        } else if (tl == l && tr == r)
            return t[v].val;
        else {
            ll tm = (tl + tr) >> 1;
            return (query(2 * v, tl, tm, l, min(r, tm)) +
                    query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r)) %
                   mod;
            // any operator instead of + depending on needs!
        }
    }

    void update(ll v, ll tl, ll tr, ll pos, ll upd) {
        if (tl == tr) {
            // comparison with upd not needed
            // obv converges
            t[v].val = upd;
        } else {
            // pos to check where to go
            ll tm = (tl + tr) >> 1;
            if (pos <= tm)
                update(2 * v, tl, tm, pos, upd);
            else
                update(2 * v + 1, tm + 1, tr, pos, upd);
            t[v].val = t[2 * v].val + t[2 * v + 1].val;
            t[v].val %= mod;
            // update after change!! (always forget)
        }
    }

  public:
    SegmentTree(const vector<ll> &a) {
        n = a.size();
        t.resize(4 * n);
        this->build(a, 1, 0, n - 1);
        // tl - tr lies in [0..n-1]
        // segtree is 1 indexed
    }

    ll query(ll l, ll r) const {
        return query(1, 0, n - 1, l, r);
        // const mem function can only call const memfunc
        // only mutable variables may be changed!
    }

    void update(ll pos, ll val) {
        // func overloaded call to distinguish!
        update(1, 0, n - 1, pos, val);
    }
};

void soln() {
    ll n;
    cin >> n;
    vector<ll> a(n);

    map<int, int> coordinate_compression;
    for (auto &x : a) {
        cin >> x;
        coordinate_compression[x]++;
    }
    int new_val = 0;
    for (auto &[key, val] : coordinate_compression) {
        val = ++new_val;
        // shifted coordinate by 1,2... in increasing order
    }
    for (int i = 0; i < n; i++)
        a[i] = coordinate_compression[a[i]];
    vector<ll> dp(n + 1);
    SegmentTree seg(dp);

    /*
    soln is dp[i] = LIS ending on index i
    dp[i] += dp[j] s.t j < i and a[j] < a[i]
    by coordinate compression, we make range query on 1...a[i]-1
    */
    for (int i = 0; i < n; i++) {
        dp[a[i]] += seg.query(0, a[i] - 1) + 1;
        dp[a[i]] %= mod;
        seg.update(a[i], dp[a[i]]);
    }

    ll sum = std::accumulate(dp.begin(), dp.end(), 0LL, [](ll acc, ll x) {
        return (acc + x) % mod;
    }); // always return new accumulator
    cout << sum << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    while (tt--) {
        soln();
    }
}
