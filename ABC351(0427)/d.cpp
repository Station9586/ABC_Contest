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

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m;

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    vector<string> gp(n);
    cin >> gp;
    auto isValid = [&] (int x, int y) -> bool {
        return x >= 0 and x < n and y >= 0 and y < m;
    };

    vector<vi> magnets(n, vi(m));
    REP (i, n) {
        REP (j, m) {
            if (gp[i][j] == '#') continue;
            int cnt = 0;
            for (int k = 0; k < 4; k ++) {
                int nx = i + dx[k], ny = j + dy[k];
                if (isValid(nx, ny) and gp[nx][ny] == '#') cnt ++;
            }
            magnets[i][j] = cnt;
        }
    }


    vector<vi> vis(n, vi(m));
    vector<vi> dp(n, vi(m));
    REP (i, n) REP (j, m) {
        if (gp[i][j] == '.') {
            if (magnets[i][j] > 0) {
                dp[i][j] = 1;
                continue;
            }
            vector<pi> q;
            q.pb({i, j});
            vis[i][j] = 1;
            for (int i = 0; i < sz(q); i ++) {
                auto [x, y] = q[i];
                if (magnets[x][y] > 0) continue;
                REP (k, 4) {
                    int nx = x + dx[k], ny = y + dy[k];
                    if (isValid(nx, ny) and gp[nx][ny] == '.' and !vis[nx][ny]) {
                        q.pb({nx, ny});
                        vis[nx][ny] = 1;
                    }
                }
            }
            for (auto [x, y]: q) {
                if (magnets[x][y] == 0) dp[x][y] = sz(q);
                else vis[x][y] = 0;
            }
        }
    }
    int ans = 0;
    REP (i, n) 
        REP (j, m) 
            ans = max(ans, dp[i][j]);
    cout << ans << "\n";
    return 0;
}