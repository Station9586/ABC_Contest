#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

using namespace std;

const int mxN = 1e6 + 10;
const ll mod = 1e9 + 7;

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

ll F[mxN], I[mxN];

int n, k;

ll C (int n, int m) {
    if (m < 0 or m > n) return 0;
    return F[n] * I[m] % mod * I[n - m] % mod;
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    F[0] = I[0] = 1;
    for (int i = 1; i < mxN; i ++) 
        F[i] = (F[i - 1] * i) % mod;

    I[mxN - 1] = power(F[mxN - 1], mod - 2);
    for (int i = mxN - 2; i >= 1; i --) 
        I[i] = I[i + 1] * (i + 1) % mod;

    ll ans = 0;

    // \sum_0^k (k - i)^n * C(k, i) * (-1)^i
    for (int i = 0; i <= k; i ++) {
        ll a = (i & 1? -1: 1);
        ll cal = (a * C(k, i) % mod * power(k - i, n) % mod + mod) % mod;
        ans = (ans + cal) % mod;
    }

    cout << ans << "\n";
    return 0;
}
