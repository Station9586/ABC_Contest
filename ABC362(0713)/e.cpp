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

template<class T> using max_heap = std::priority_queue<T>;
template<class T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template<class T> bool chmin (T &a, const T &b) { return a > b? (a = b, true): false; }
template<class T> bool chmax (T &a, const T &b) { return a < b? (a = b, true): false; }
template<class T> std::vector<T> sort_unique (std::vector<T> &v) { std::sort(all(v)), v.erase(std::unique(all(v)), v.end()); return v; }

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

const int mxN = 81;
const ll mod = 998244353;

int n;

vi v(mxN);
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    FOR (i, 1, n) cin >> v[i];

    vector dp(mxN, vector(mxN, vector<ll>(mxN, 0))); // 倒數第二, 倒數第一, 選了幾個
    FOR (i, 1, n) {
        auto nxt = dp;
        nxt[0][i][1] = 1; // 從 i 開始只選一個: 1
        FOR (j, 1, i - 1) 
            nxt[j][i][2] = (nxt[j][i][2] + dp[0][j][1]) % mod; // 選兩個
        FOR (j, 1, i - 1) FOR (k, j + 1, i - 1) FOR (l, 1, i - 1) { // j, k, i
            if (v[i] - v[k] != v[k] - v[j]) continue; // 不是等差
            nxt[k][i][l + 1] = (nxt[k][i][l + 1] + dp[j][k][l]) % mod;
        }
        dp = nxt;
    }

    FOR (i, 1, n) {
        ll ans = 0;
        FOR (j, 0, n) FOR (k, 0, n) {
            ans = (ans + dp[j][k][i]) % mod;
        }
        cout << ans << " \n"[i == n];
    }
    return 0;
}