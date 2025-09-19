#include <bits/stdc++.h>
#define ll long long int
using namespace std;

constexpr int N = 100001;

int main() {
    std::bitset<N> possible;
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (auto &x : a)
        cin >> x;
    possible.set(0); // set LSB ie 0 true

    for (int i = 0; i < n; i++) {
        possible = (possible | (possible << a[i]));
    }
    vector<ll> ans;
    for (int i = 1; i <= N; i++) {
        if (possible[i] > 0) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << "\n";
    for (auto v : ans)
        cout << v << " ";
}