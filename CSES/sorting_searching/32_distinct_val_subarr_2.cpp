#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int main() {
    /*
    if l...r has <= k  distinct val, so does all its subarrays
    maintain a queue with <= k distinct val ending at r,
    then add all possible subarrays ending at r..
    since any j < l will introduce more distinct values,
    this two pointer property holds.
    */

    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (auto &x : a)
        cin >> x;
    map<ll, ll> freq;
    ll ans = 0;
    ll l = 0;
    for (int r = 0; r < n; r++) {
        freq[a[r]]++;
        while (freq.size() > k) {
            freq[a[l]]--;
            if (freq[a[l]] == 0)
                freq.erase(a[l]);
            l++;
        }
        ans += (r - l + 1);
    }
    cout << ans << "\n";
}