#include <bits/stdc++.h>
#define ll long long int

using namespace std;

constexpr ll N = 2e5 + 2;

int main() {
    /*

    naturally keep it in sorted order of end times
    I was using vector like approach by assigning members in order...
    this created problem if [57...69] [77....84], it is best to re-use
    the 69 guy..
    so we use multiset to track when each member becomes free
    and for each movie , assign the guy who gets free the latest.
    */
    ll n, k;
    cin >> n >> k;
    multiset<ll> available;
    for (int i = 0; i < k; i++)
        available.insert(0);
    vector<pair<ll, ll>> times(n);
    for (int i = 0; i < n; i++) {
        cin >> times[i].first >> times[i].second;
    }
    sort(times.begin(), times.end(),
         [](const pair<ll, ll> &a, const pair<ll, ll> &b) {
             if (a.second != b.second)
                 return a.second < b.second;
             else
                 return a.first < b.first;
         });

    ll ans = 0;

    for (int i = 0; i < n; i++) {

        auto it = available.upper_bound(times[i].first);
        if (it != available.begin()) {
            it--;
            ans++;
            available.erase(it);
            available.insert(times[i].second);
        }
    }
    cout << ans << "\n";
}