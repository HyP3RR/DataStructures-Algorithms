#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int main() {

    ll n;
    cin >> n;
    vector<ll> a(n);
    for (auto &x : a)
        cin >> x;
    ll dp[n + 1][n + 1]
         [2]; // max sum for first player if subarr [i , i + l - 1] and player
    // k moves first.

    for (int l = 1; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            if (l == 1) {
                dp[i][l][0] = a[i];
                dp[i][l][1] = 0;
            } else {
                dp[i][l][0] = max(dp[i][l - 1][1] + a[i + l - 1],
                                  dp[i + 1][l - 1][1] + a[i]);
                dp[i][l][1] = min(
                    dp[i][l - 1][0],
                    dp[i + 1][l - 1][0]); // 1 tries to minimise earnings for
                                          // 0th player by taking max val.
            }
        }
    }
    cout << dp[0][n][0];
}