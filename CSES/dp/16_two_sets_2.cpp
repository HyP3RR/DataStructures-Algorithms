#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const ll mod = 1e9 + 7;

ll mult(ll a, ll b) { return ((a % mod) * (b % mod)) % mod; }

ll binpow(ll a, ll b) {
    if (b == 0)
        return 1;
    ll ans = binpow(a, b / 2);
    if (b % 2 == 0)
        return mult(ans, ans);
    else
        return mult(ans, mult(ans, a));
}

ll inv(ll a) { return binpow(a, mod - 2); }

int main() {
    /*
    simply count ways to make (N*(N+1))/4 and we know
    if sum = X has set T, sum = TSUM - X has set complement of t
    here X is total sum / 2 , so we divide answer by two here

    */
    ll n;
    cin >> n;
    if ((n * (n + 1)) % 4 != 0) {
        cout << 0 << "\n";
        return 0;
    }
    ll W = (n * (n + 1)) / 4 + 2;
    ll dp[W];
    for (int i = 0; i < W; i++)
        dp[i] = 0;
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = W - 1; j > 0; j--) {
            if (j - i >= 0) {
                dp[j] += dp[j - i];
                dp[j] %= mod;
            }
        }
    }
    cout << mult(dp[(n * (n + 1)) / 4], inv(2));
}