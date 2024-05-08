#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

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

template<class T> constexpr T fld (const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }
template<class T> constexpr T cld (const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }
template<typename T> inline T __lg (T __n) { T __k; for (__k = 0; __n != 0; __n >>= 1) ++ __k; return __k - 1; }

using namespace std;

const ll mod = 1e9 + 7;
const int mxN = 2e6 + 10;

int adj[25][25];
ll dp[25][mxN];

int p[25];

vi v[25];
vi rcd[mxN];

int n, m;

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    int a, b;
    for (int i = 0; i < m; i ++) {
        cin >> a >> b;
        a --, b --;
        adj[a][b] ++;
    }
    dp[0][1] = 1;
    for (int i = 0; i <= n; i ++) p[i] = 1 << i;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n - 1; j ++) {
            if (i != j and adj[j][i]) {
                for (int k = 0; k < adj[j][i]; k ++) v[i].pb(j);
            }
        }
    }
    for (int i = 1; i < p[n]; i ++) {
        for (int j = 1; j < n; j ++) {
            if (i & p[j]) rcd[i].pb(j);
        }
    }
    for (int i = 1; i < p[n]; i += 2) {
        for (auto j: rcd[i]) {
            int now = i ^ (p[j]);
            for (auto k: v[j]) dp[j][i] += dp[k][now];
            dp[j][i] %= mod;
        }
    }
    cout << dp[n - 1][p[n] - 1] << "\n";
    return 0;
}