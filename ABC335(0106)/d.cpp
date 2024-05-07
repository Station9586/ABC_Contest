#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

namespace Station {
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
};

using namespace std;
using namespace Station;

const int mxN = 2e5 + 10;

int n, k;

vi gp[mxN];

int mx = -1;
int sub[mxN];
int cnt[mxN], vis[mxN];

ll ans = 0;

int get_size (int a, int pre) { // Count subtree size
    sub[a] = 1;
    for (int i: gp[a]) {
        if (i != pre and !vis[i]) 
            sub[a] += get_size(i, a);
    }
    return sub[a];
}

int Find (int a, int pre, int n) { // Get Centroid
    for (int i: gp[a]) {
        if (i == pre) continue;
        if (!vis[i] and sub[i] > n / 2) 
            return Find(i, a, n); 
    }
    return a;
}

void dfs (int a, int pre, bool ok, int dep = 1) { // Centriod Decomposition
    if (dep > k) return;
    mx = max(mx, dep);
    if (ok) cnt[dep] ++;
    else ans += cnt[k - dep];
    for (int i: gp[a]) {
        if (i != pre and !vis[i]) 
            dfs(i, a, ok, dep + 1);
    }
}

void solve (int a) {
    int centre = Find(a, 0, get_size(a, 0));
    vis[centre] = 1;
    mx = 0;
    for (int i: gp[centre]) {
        if (!vis[i]) {
            dfs(i, centre, 0);
            dfs(i, centre, 1);
        }
    }
    fill(cnt + 1, cnt + 1 + mx, 0);
    for (auto i: gp[centre]) {
        if (!vis[i]) solve(i);
    }
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    int a, b;
    for (int i = 0; i < n - 1; i ++) {
        cin >> a >> b;
        gp[a].pb(b);
        gp[b].pb(a);
    }
    cnt[0] = 1;
    solve(1);
    cout << ans << "\n";
    return 0;
}