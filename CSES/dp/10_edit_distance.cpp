#include <bits/stdc++.h>
#define ll long long int

using namespace std;

constexpr int maxn = 5001;

int dp[maxn][maxn];

int main() {
    /*
    dp[i][j] is operation s.t. a[0..i] and b[0..j] become same
    if ai == bj then we can do dp[i-1][j-1]
    otherwise, replacing is dp[i-1][j-1] + 1
    remove ai -> dp[i-1][j] + 1
    insert bj -> dp[i][j-1] + 1 ... i,j same since we dont index the added
    character so match i,j-1 and add bj in front of ai... considering this is
    fine as doing opposite is symmetrical too
    */
    string a;
    string b;
    cin >> a >> b;
    int n = a.length();
    int m = b.length();
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            if (j == 0 || i == 0)
                dp[i][j] = max(i, j);
            else
                dp[i][j] = 1e8;
        }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] =
                    min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
            }
        }
    }

    cout << dp[n][m] << "\n";
}