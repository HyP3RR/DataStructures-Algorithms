#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int dp[501][501];
int main() {
    /*
    weirdly, greedy solution not working.
    so dp soln is simple, axb we can cut along each row or columns

    we need to process cuttings in incremental sizes (ie rows + columns)
    so we will have an answer for smaller row or column too!

    simple dp to find i,j then find cutting for k where k is row/col along which
    you cut.
    */
    int a, b;
    cin >> a >> b;
    for (int i = 0; i <= 500; i++)
        for (int j = 0; j <= 500; j++)
            dp[i][j] = 1e8;
    for (int i = 0; i <= 500; i++) {
        dp[i][i] = 0;
    }
    for (int size = 2; size <= a + b; size++) {
        for (int side = 1; side <= size; side++) {
            int i = side;
            int j = size - side;
            if (i < 0 || j < 0 || i > 500 || j > 500)
                continue;
            for (int k = 1; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
            }
            for (int k = 1; k < i; k++) {
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
            }
        }
    }
    cout << dp[a][b];
}