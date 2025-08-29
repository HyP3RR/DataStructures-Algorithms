#include <bits/stdc++.h>
#define ll long long int
using namespace std;

constexpr ll MAXN = 2e5 + 2;
constexpr ll mod = 1e9 + 7;

ll tilings[1001][(1 << 10)];
// by default on .bss, so 0 val.

ll n, m;

void fill_column(int col, int idx, int curr_mask, int next_mask) {
    // curr_mask is the perma mask, which is left due to process  of prev
    // columns! so never changed!

    if (idx == n) {
        // column filled!, propagate to next mask
        tilings[col + 1][next_mask] += tilings[col][curr_mask];
        tilings[col + 1][next_mask] %= mod;
        return;
    }
    if ((curr_mask) & (1 << idx)) {
        // this cell filled! move
        fill_column(col, idx + 1, curr_mask, next_mask);
    } else {
        // fill this cell by | or --
        fill_column(col, idx + 1, curr_mask, next_mask | (1 << idx)); // fill --
        if (idx + 1 < n && (!(curr_mask & (1 << (idx + 1))))) {
            // space for | and if idx+1 also empty!
            fill_column(col, idx + 2, curr_mask, next_mask);
        }
    }
}

void soln() {
    // couldnt think of this one on my own

    cin >> n >> m;
    /*
    -- 1
    |  0
    -- 1

    if on column i,
    you put tiles aise hee
    and it protudes on i+1
    1 represents if j+1
    cell is filled, 0 if it
    was left empty because of how
    i set it up (or messed it up
    for j+1)

    so for each mask X on j
    we allocate tiles, which
    result in mask Y for j+1
    so dp[j+1][Y] += dp[j][X]

    highest order at bottom (bit)

    complexity: O(m*2^n * n)
    O(n) due to transitions on single
    column

    ans: dp[n][0] (no further mask for n+1)

    transition:
    for a column (iterate over row)
    either place  | - , or skip if filled
    */

    tilings[0][0] = 1;

    for (ll column = 0; column < m; column++) {
        for (ll mask = 0; mask < (1 << n); mask++) {
            if (tilings[column][mask] > 0) {
                // process this mask and add it for j+1
                // ie process column
                fill_column(column, 0, mask, 0);
            }
        }
    }
    cout << tilings[m][0] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    while (tt--) {
        soln();
    }
}