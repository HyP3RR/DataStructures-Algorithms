#include <bits/stdc++.h>
#define ll long long int
using namespace std;

constexpr ll MAXN = 2e5 + 2;
constexpr ll mod = 1e9 + 7;

pair<int, int> best[1 << 20];

int max(int a, int b) { return (a > b ? a : b); }

void soln() {
    int n, w;
    cin >> n >> w;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;

    /*
    initial approach:
    dp[i][j] max weight available
    in last ride if
    i rides and j subset group taken

    problem: n*2^n*n
    the dp table is very sparse!
    mostly -1!

    we are never using i for transition,
    it is unnecessary!
    we technically only care about dp[j]
    whether it is i-1 or i it is irrelevant!

    idea:
    for subset i people
    best[i].first -> min rides needed
    best[i].second -> max weight available
    for the last ride
    direct transition for any subset.

    O(n*2^n)
    */
    best[0] = {1, 0}; // 1 ride, 0 filled
    // minimise this, least  ride and least filled
    for (int mask = 1; mask < (1 << n); mask++) {
        pair<int, int> bestopn = {n, 0}; // worst case
        for (int k = 0; k < n; k++) {
            if ((mask >> k) & 1) {
                auto &[rides, filled] = best[(1 << k) ^ mask];

                if (filled + a[k] <= w) {
                    bestopn = min(bestopn, {rides, filled + a[k]});
                } else {
                    bestopn = min(bestopn, {rides + 1, a[k]});
                }
            }
        }
        best[mask] = bestopn;
    }
    cout << best[(1 << n) - 1].first << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    while (tt--) {
        soln();
    }
}