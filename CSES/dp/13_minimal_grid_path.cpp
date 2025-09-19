#include <bits/stdc++.h>
#define ll long long int

using namespace std;

char a[3001][3001];

int main() {
    /*
    we iterate over diagonals, forming our best estimate
    by greedily marking prev diagonal indices 1 if they were
    the best estimate (ie least string)
    we consider those ancestor as candidates for current diagonal
    index... and we find the least lexographically valid char
    and mark those diagonal indices true for next iteration..
    */

    int n;
    cin >> n;

    vector<vector<int>> dp(n, vector<int>(n)); // for n = 3000 stack overflow.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            dp[i][j] = 0;
        }
    }
    string ans;
    for (int diag = 0; diag < 2 * n - 1; diag++) {
        if (diag == 0) {
            ans += a[0][0];
            dp[0][0] = 1;
            continue;
        }
        char best = 'Z';
        for (int r = 0; r <= diag; r++) {
            int i = r;
            int j = diag - r;
            if (i < 0 || i >= n || j < 0 || j >= n)
                continue;
            if (i > 0 && dp[i - 1][j] == 1)
                best = min(best, a[i][j]);
            if (j > 0 && dp[i][j - 1] == 1)
                best = min(best, a[i][j]);
        }
        ans += best;
        for (int r = 0; r <= diag; r++) {
            int i = r;
            int j = diag - r;
            if (i < 0 || i >= n || j < 0 || j >= n)
                continue;
            if (a[i][j] == best) {
                if ((i > 0 && dp[i - 1][j] == 1) ||
                    (j > 0 && dp[i][j - 1] == 1))
                    dp[i][j] = 1;
            }
        }
    }
    cout << ans << "\n";
}