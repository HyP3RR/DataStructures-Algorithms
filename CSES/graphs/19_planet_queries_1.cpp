#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int main() {
    /*
    classic binary jumping

    */
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<array<int, 32>> nxt(n);

    for (int i = 0; i < n; i++) {
        cin >> nxt[i][0];
        nxt[i][0]--;
    }

    for (int j = 1; j < 32; j++) {
        for (int i = 0; i < n; i++) {
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        }
    }

    while (q--) {
        int x, k;
        cin >> x >> k;
        x--;
        int ans = x;

        for (int i = 30; i >= 0; i--) {
            if ((k >> i) & 1) {
                ans = nxt[ans][i];
            }
        }

        cout << ans + 1 << "\n";
    }
}