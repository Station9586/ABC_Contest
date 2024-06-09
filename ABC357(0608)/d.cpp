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

ll n;
ll power (ll x, ll p) {
    ll ret = 1;
    x %= mod;
    while (p) {
        if (p & 1) ret = ret * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return ret;
}

ll inv (ll x) { return power(x, mod - 2); }

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    ll x = n;
    ll k = 1;
    while (x) {
        x /= 10;
        k *= 10;
        k %= mod;
    }

    ll ans = n * (power(k, n) - 1ll) % mod * inv(k - 1ll) % mod;
    cout << ans % mod << "\n";
    return 0;
}