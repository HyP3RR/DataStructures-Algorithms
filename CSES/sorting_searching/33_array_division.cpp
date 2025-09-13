#include <bits/stdc++.h>
#define ll long long int

using namespace std;

constexpr ll N = 2e5 + 2;
ll n, k;
vector<ll> a(N);

bool check(ll maxum) {
    ll subarr = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > maxum)
            return false;
    }
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        if (sum + a[i] > maxum) {
            subarr++;
            sum = a[i];
        } else {
            sum += a[i];
        }
    }
    if (sum > 0)
        subarr++;
    return subarr <= k;
}

int main() {
    cin >> n >> k;
    /*
    fix max sum = mid,
    if number of subarrays needed to divide it > k
    then maxsum must be greater
    otherwise we can reduce maxsum
    */
    for (int i = 0; i < n; i++)
        cin >> a[i];

    ll i = 0;
    ll j = 1e17;
    ll mid;

    while (i <= j) {
        mid = (i + j) >> 1;
        if (i == j)
            break;
        if (check(mid) == true)
            j = mid;
        else {
            i = mid + 1;
        }
    }
    // first mid which is true , ie ans = mid;
    cout << mid << "\n";
}