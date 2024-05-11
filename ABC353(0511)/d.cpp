#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())
#define FOR(i, a, b) for (int i = a; i <= b; i ++)
#define REP(i, b) for (int i = 0; i < b; i ++)
#define IFOR(i, a, b) for (int i = b - 1; i >= a; i --) 

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

using namespace std;

const ll mod = 998244353;

int n;
ll ans, m, s;

ll power (ll x, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p & 1) ret = ret * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return ret;
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    vector<ll> v(n);
    vector<ll> cnt_10(n);
    REP (i, n) {
        cin >> v[i];
        ll tmp = v[i];
        int cnt = 0;
        while (tmp) {
            tmp /= 10;
            cnt ++;
        }
        cnt_10[i] = cnt;
    }

    IFOR (i, 0, n) {
        ans += v[i] * m + s;
        ans %= mod;
        m += power(10ll, cnt_10[i]);
        m %= mod;
        s += v[i];
        s %= mod;
    }

    cout << ans << '\n';
    return 0;
}