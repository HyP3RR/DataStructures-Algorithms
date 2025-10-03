#include <bits/stdc++.h>
#define ll long long int

using namespace std;
int dp[1001][1001];
int main() {
    /*
    standard, best to go towards with max current subsequence.

    */
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> b(m);
    for (auto &x : a)
        cin >> x;
    for (auto &x : b)
        cin >> x;

    int prev[n + 1][m + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 || j == 0) {
                if (i > 0)
                    dp[i][j] = dp[i - 1][j];
                if (j > 0)
                    dp[i][j] = max(dp[i][j], dp[i][j - 1]);
                dp[i][j] =
                    (a[i] == b[j]
                         ? 1
                         : dp[i]
                             [j]); // always handle this case, since for 0 ind
                                   // we may have other j/i which can be equal

            } else {
                int v = max({dp[i - 1][j], dp[i][j - 1],
                             dp[i - 1][j - 1] + (a[i] == b[j])});
                dp[i][j] = v;
            }
        }
    }

    vector<int> ans;
    int i = n - 1;
    int j = m - 1;
    while (i > -1 && j > -1) {
        if (a[i] == b[j]) {
            ans.push_back(a[i]);
            i--;
            j--;
        } else {
            if (dp[i - 1][j] > dp[i][j - 1])
                i--;
            else
                j--;
        }
    }
    cout << dp[n - 1][m - 1] << "\n";
    reverse(ans.begin(), ans.end());
    for (auto &x : ans)
        cout << x << " ";
}