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

const int mxN = 1010;
const int mxY = 1e5 + 10;

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

queue<pi> q[mxY];
int gp[mxN][mxN];

bool in[mxN][mxN];
int h, w, n;

inline bool isValid (const int x, const int y) {
    if (x >= 0 and x < h and y >= 0 and y < w and in[x][y]) return true;
    return false;
}

inline bool isBoundary (const int x, const int y) {
    if (x == 0 or x == h - 1 or y == 0 or y == w - 1) return true;
    return false;
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> h >> w >> n;
    REP (i, h) REP (j, w) {
        cin >> gp[i][j];
        in[i][j] = 1;
        if (isBoundary(i, j)) {
            in[i][j] = false;
            q[gp[i][j]].push({i, j});
        }
    }

    int ans = h * w;
    FOR (i, 1, n) {
        while (!q[i].empty()) {
            ans --;
            auto [x, y] = q[i].front();
            q[i].pop();
            REP (k, 4) {
                int nx = x + dx[k], ny = y + dy[k];
                if (isValid(nx, ny)) {
                    in[nx][ny] = 0;
                    q[max(gp[nx][ny], i)].push({nx, ny});
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}