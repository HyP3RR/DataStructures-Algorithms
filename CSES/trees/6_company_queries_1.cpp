#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 2;

int jmp[30][MAXN];

int main() {
    int n, q;
    cin >> n >> q;

    memset(jmp, -1, sizeof(jmp));
    for (int i = 1; i < n; i++) {
        int v;
        cin >> v;
        v--;
        jmp[0][i] = v;
    }
    for (int i = 1; i < 30; i++) {
        for (int j = 0; j < n; j++) {
            if (jmp[i - 1][j] != -1)
                jmp[i][j] = jmp[i - 1][jmp[i - 1][j]];
        }
    }
    while (q--) {
        int x, k;
        cin >> x >> k;
        x--;
        int ans = x;
        for (int i = 0; i < 30; i++) {
            int v = ((k >> i) & 1);
            if (v)
                ans = jmp[i][ans];
        }
        cout << (ans == -1 ? -1 : ans + 1) << "\n";
    }
}