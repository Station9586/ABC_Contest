#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

template<class a> std::ostream& operator << (std::ostream& out, std::vector<a>& v) { for (auto i: v) out << i << " "; return out; }
template<typename... T> void read (T&... args) { ((std::cin >> args), ...); }
template<typename... T> void put (T&&... args) { ((std::cout << args << " "), ...); }
template<typename... T> void print (T&&... args) { ((std::cout << args << " "), ...); std::cout << "\n"; }

template<class T> using max_heap = std::priority_queue<T>;
template<class T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template<class T> bool chmin (T &a, const T &b) { return a > b? (a = b, true): false; }
template<class T> bool chmax (T &a, const T &b) { return a < b? (a = b, true): false; }
template<class T> std::vector<T> sort_unique (std::vector<T> v) { std::sort(all(v)), v.erase(std::unique(all(v)), v.end()); return v; }

template<class T, class U> std::istream& operator >> (std::istream& in, std::pair<T, U>& p) { in >> p.first >> p.second; return in; }
template<class T, size_t N> std::istream& operator >> (std::istream& in, std::array<T, N>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::istream& operator >> (std::istream& in, std::vector<T>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::ostream& operator << (std::ostream& out, std::vector<T>& a) { for (T x: a) out << x << " "; return out; }

template<class T> constexpr T fld (const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }
template<class T> constexpr T cld (const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }
template<typename T> inline T __lg (T __n) { T __k; for (__k = 0; __n != 0; __n >>= 1) ++ __k; return __k - 1; }

using namespace std;

const int mxN = 2e5 + 10;

int n;
ll mod;

ll power (ll x, ll p, ll mod) {
    ll cal = 1;
    x %= mod;
    while (p) {
        if (p & 1) cal = (__int128)cal * x % mod;
        x = (__int128)x * x % mod;
        p >>= 1;
    }
    return cal;
}

ll num[mxN];

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> mod;
    for (int i = 1; i <= n; i ++) cin >> num[i];
    vector<ll> pri, fac;
    ll t = mod - 1;
    for (ll i = 1; i * i <= t; i ++) {
        if (t % i == 0) {
            fac.emplace_back(i);
            if (i * i < t) fac.emplace_back(t / i);
        }
    }
    sort(all(fac));
    for (ll i = 2; i * i <= t; i ++) {
        if (t % i == 0) {
            pri.emplace_back(i);
            while (t % i == 0) t /= i;
        }
    }
    if (t > 1) pri.emplace_back(t);
    sort(all(pri));
    vector<ll> cnt(sz(fac));
    for (int i = 1; i <= n; i ++) {
        ll e = mod - 1;
        for (auto j: pri) {
            while (e % j == 0 and power(num[i], e / j, mod) == 1) e /= j;
        }
        int id = lower_bound(all(fac), e) - fac.begin();
        cnt[id] ++;
    }
    ll ans = 0;
    for (int i = 0; i < sz(fac); i ++) {
        for (int j = i; j < sz(fac); j ++) {
            if (fac[j] % fac[i] == 0) ans += cnt[i] * cnt[j];
        }
    }
    cout << ans << "\n";
    return 0;
}