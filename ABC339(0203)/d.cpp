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

const int INF = 1e9 + 7;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

int n;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    vector<string> gp(n);
    cin >> gp;
    vector<vi> dis(n * n, vi(n * n, INF));

    int p1 = -1, p2 = -1;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            if (gp[i][j] == 'P') {
                if (p1 == -1) p1 = i * n + j;
                else p2 = i * n + j;
            }
        }
    }

    queue<pi> q;
    q.push({p1, p2});
    dis[p1][p2] = 0;

    auto isValid = [&] (int x, int y, int k) -> pi {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 or nx >= n or ny < 0 or ny >= n or gp[nx][ny] == '#') return {x, y};
        return {nx, ny};
    };

    while (!q.empty()) {
        auto [a, b] = q.front();
        q.pop();
        if (a == b) {
            cout << dis[a][b] << "\n";
            return 0;
        }

        int p1x = a / n, p1y = a % n;
        int p2x = b / n, p2y = b % n;

        for (int k = 0; k < 4; k ++) {
            pi nx1 = isValid(p1x, p1y, k);
            pi nx2 = isValid(p2x, p2y, k);

            int n1 = nx1.first * n + nx1.second;
            int n2 = nx2.first * n + nx2.second;
            
            if (chmin(dis[n1][n2], dis[a][b] + 1)) q.push({n1, n2});
        }
    }
    cout << "-1\n";
    return 0;
}