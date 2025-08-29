#include <bits/stdc++.h>
#define ll long long int
using namespace std;

constexpr ll MAXN = 2e5 + 2;

void soln() {
    ll n;
    cin >> n;
    vector<array<ll, 3>> projects(n);
    for (int i = 0; i < n; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        projects[i] = {a, b, w};
    }

    sort(projects.begin(), projects.end());
    vector<ll> next(n + 1);
    // next[i] = j is the earliest next project we
    // can pick after finishing i

    /*
    dp[i] = max(dp[i+1],dp[next[i]]+w[i])
    it is the max val we can get if we start from i
    (not necessarily pick i)

    so if there exists an optimal sequence from a..b..c
    we consider all, even if we dont greedily pick the
    earliest next project and skip it! (hence dp[i+1])

    only greedily picking earliest next project would be wrong,
    as we fix the greedy approach of taking earlist instead
    of skipping j and wait for some higher valued ones
    */
    for (int i = 0; i < n; i++) {
        int end = projects[i][1];
        std::array<ll, 3> agla = {end + 1, 0, 0};
        int ind = lower_bound(projects.begin(), projects.end(), agla) -
                  projects.begin();

        next[i] = ind;
        // if no next,  by default n (0)
    }
    vector<ll> dp(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        ll w = projects[i][2];
        dp[i] = max(dp[i + 1], dp[next[i]] + w);
    }
    cout << dp[0] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    while (tt--) {
        soln();
    }
}