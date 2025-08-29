#include <bits/stdc++.h>
#define ll long long int
using namespace std;

bool check(ll n) {
    ll prev = -1;
    while (n > 0) {
        if (prev == n % 10)
            return false;
        prev = n % 10;
        n -= n % 10;
        n /= 10;
    }
    return true;
}

ll till_n(ll n) {
    ll tmp = n;
    ll pow10 = 1;
    while (tmp >= 10) {
        tmp /= 10;
        pow10 *= 10;
    }
    vector<ll> dp;
    tmp = n;
    while (pow10 > 0) {
        dp.push_back(tmp / pow10);
        tmp %= pow10;
        pow10 /= 10;
    }
    //form dp which is technically number
    //written left to right..
    vector<ll> ans(20, 1);
    tmp = 9;
    for (int i = 1; i < 20; i++) {
        ans[i] = tmp;
        tmp *= 9;
    }

    //ans[i] is options to put i numbers
    //s.t. no leading zeros (ie not first number)

    ll sol = 0;
    sol = (ans[dp.size()] - 1) / 8; //consider case 0....10000 alag se sum
    ll prev = dp[0];
    sol += (dp[0] - 1) * ans[dp.size() - 1]; //100...X000 by using ans[i]!!
    for (int i = 1; i < dp.size(); i++) {
        sol += (dp[i] - (prev < dp[i])) * ans[dp.size() - i - 1];
        if (dp[i] == prev)
            break;
        prev = dp[i];
        //basic digit transition
        //if [2, 0 , 2 , 2]
        //we process 2 and break if same as prev
        //1 less number if prev no.  < current number. 
        //now update number as 2 and keep checking
    }
    return sol + check(n); //finally only n left to check!
}

ll brute(ll n) {
    ll sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += check(i);
    }
    return sum;
}

void soln() {
    ll a, b;
    cin >> a >> b;

    cout << till_n(b) - till_n(a) + check(a);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    while (tt--) {
        soln();
    }
}
