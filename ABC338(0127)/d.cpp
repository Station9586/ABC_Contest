#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

template<class T> using max_heap = std::priority_queue<T>;
template<class T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template<class T> bool chmin (T &a, const T &b) { return a > b? (a = b, true): false; }
template<class T> bool chmax (T &a, const T &b) { return a < b? (a = b, true): false; }
template<class T> std::vector<T> sort_unique (std::vector<T> v) { std::sort(all(v)), v.erase(std::unique(all(v)), v.end()); return v; }

template<class T, class U> std::istream& operator >> (std::istream& in, std::pair<T, U>& p) { in >> p.first >> p.second; return in; }
template<class T, size_t N> std::istream& operator >> (std::istream& in, std::array<T, N>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::istream& operator >> (std::istream& in, std::vector<T>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::ostream& operator << (std::ostream& out, std::vector<T>& a) { for (T x: a) out << x << " "; return out; }

template<typename... T> void read (T&... args) { ((std::cin >> args), ...); }
template<typename... T> void put (T&&... args) { ((std::cout << args << " "), ...); }
template<typename... T> void print (T&&... args) { ((std::cout << args << " "), ...); std::cout << "\n"; }

template<class T> constexpr T fld (const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }
template<class T> constexpr T cld (const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }
template<typename T> inline T __lg (T __n) { T __k; for (__k = 0; __n != 0; __n >>= 1) ++ __k; return __k - 1; }

using namespace std;

const ll INF = 1e18;

int n, m;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    vi order(m);
    for (int &i: order) {
        cin >> i;
        i --;
    }

    vector<ll> dp(n + 1);
    auto dis = [&] (int u, int v) {
        if (u < v) return v - u;
        return v - u + n;
    };

    auto add = [&] (int u, int v, int num) {
        if (u <= v) {
            dp[u] += num;
            dp[v] -= num;
        }else {
            dp[u] += num;
            dp[n] -= num;
            dp[0] += num;
            dp[v] -= num;
        }
    };

    for (int i = 0; i < m - 1; i ++) {
        add(order[i], order[i + 1], dis(order[i + 1], order[i]));
        add(order[i + 1], order[i], dis(order[i], order[i + 1]));
    }

    ll ans = INF;
    for (int i = 0; i < n; i ++) {
        dp[i + 1] += dp[i];
        ans = min(ans, dp[i]);
    }
    cout << ans << '\n';
    return 0;
}