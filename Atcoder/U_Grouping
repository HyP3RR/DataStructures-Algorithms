#include <bits/stdc++.h>
#define ll long long int
using namespace std;

constexpr ll MAXN = 2e5 + 2;
constexpr ll mod = 1e9 + 7;

int max(int a, int b) { return (a > b ? a : b); }

// atcoder U grouping
ll dp[(1 << 16)];
/*
technique: iterating over all submask of mask M.
in complexity of O(3^n)

dp[mask] is the max score s.t.
all 1's are left (or in group (i,i))
all 0's are grouped in SOME set

obv due to "some" problem, we have option
to pick any submask and consider that grouping as
a possibility.

so dp[mask] = max(dp[submask] + pick(submask^mask))
into one group. obv pick must be simulated by nC2 logic
*/

ll a[16][16];
ll n;

unordered_map<ll, ll> subset_value;

// optimise, pre-calculate pick!
void pick(ll mask) {
    vector<ll> cur_set;
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) {
            cur_set.push_back(i);
        }
    }
    ll ans = 0;
    for (int i = 0; i < cur_set.size(); i++) {
        for (int j = 0; j < i; j++) {
            int x = cur_set[i];
            int y = cur_set[j];
            ans += a[x][y];
        }
    }
    subset_value[mask] = ans;
}

void soln() {

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    //[n-1 , n-2 ... 0] indices pick option
    // pre-calc all possible set of pick
    for (int mask = 1; mask < (1 << n); mask++) {
        pick(mask);
    }

    for (int mask = 1; mask < (1 << n); mask++) {
        dp[mask] = subset_value[mask]; // optimse
        for (int submask = mask;; submask = (submask - 1) & mask) {
            dp[mask] =
                max(dp[mask],
                    dp[submask] +
                        dp[submask ^ mask]); // optimally do O(1) lookup, by
                                             // initialising dp by subset
            if (submask == 0)
                break;

            /*
            intuition:
            mask is 10011001100
            submask being submask-1
            makes all bits on right of 1 , also 1
            (useless)
            so we & it with mask to consider only valid
            submasks!
            */
        }
    }

    cout << dp[(1 << n) - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    while (tt--) {
        soln();
    }
}