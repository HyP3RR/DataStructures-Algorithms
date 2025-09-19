#include <bits/stdc++.h>
#define ll long long int

using namespace std;
int dp[1001][1001];
int main() {
    /*
    standard, although weird method to print answer.

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
                prev[i][j] = -1;
            } else {
                int v = max({dp[i - 1][j], dp[i][j - 1],
                             dp[i - 1][j - 1] + (a[i] == b[j])});
                dp[i][j] = v;
                if (dp[i - 1][j] == v)
                    prev[i][j] = 0;
                else if (dp[i][j - 1] == v)
                    prev[i][j] = 1;
                else
                    prev[i][j] = 2;
            }
        }
    }
    cout << dp[n - 1][m - 1] << "\n";
    vector<int> ans;
    int i = n - 1;
    int j = m - 1;
    while (prev[i][j] != -1 && i > 0 && j > 0) {
        if (prev[i][j] == 2) {
            ans.push_back(a[i]);
            i--;
            j--;
        } else {
            if (prev[i][j] == 0)
                i--;
            if (prev[i][j] == 1)
                j--;
        }
    }
    if (a[i] == b[j])
        ans.push_back(a[i]);
    else {
        while (j > 0) {
            if (a[i] == b[j]) {
                ans.push_back(a[i]);
                j = 0;
                i = 0;
                break;
            }

            j--;
        }
        while (i > 0) {
            if (a[i] == b[j]) {
                ans.push_back(a[i]);
                j = 0;
                i = 0;
                break;
            }

            i--;
        }
    }

    reverse(ans.begin(), ans.end());
    for (auto &x : ans)
        cout << x << " ";
}