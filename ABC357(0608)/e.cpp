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

const int mxN = 2e5 + 10;

int n;
vi gp[mxN];
vi rev[mxN];

bool vis[mxN];
stack<int> stk;

int scc[mxN];
int _id;

int SZ[mxN];

vi nw[mxN];

int in[mxN];

ll ans;

void dfs1 (int a) {
    vis[a] = 1;
    for (int i: gp[a]) {
        if (!vis[i])
            dfs1(i);
    }
    stk.push(a);
}

void dfs2 (int a) {
    vis[a] = 1;
    scc[a] = _id;
    SZ[_id] ++;
    for (int i: rev[a]) {
        if (!vis[i])
            dfs2(i);
    }
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    int a;
    FOR (i, 1, n) {
        cin >> a;
        gp[i].pb(a);
        rev[a].pb(i);
    }
    
    FOR (i, 1, n) {
        if (!vis[i]) dfs1(i);
    }

    memset(vis, 0, sizeof(vis));
    while (!stk.empty()) {
        int now = stk.top();
        stk.pop();
        if (vis[now]) continue;
        _id ++;
        dfs2(now);
    }

    FOR (i, 1, n) {
        for (int j: gp[i]) {
            if (scc[i] != scc[j]) {
                nw[scc[i]].pb(scc[j]);
                in[scc[j]] ++;
            }
        }
    }
    vi dp(mxN);
    queue<int> q;
    FOR (i, 1, _id) {
        if (!in[i]) {
            q.push(i);
            dp[i] = 1;
        }
    }

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        ans += dp[now] * SZ[now];
        for (int i: nw[now]) {
            in[i] --;
            dp[i] += dp[now];
            if (!in[i]) {
                q.push(i);
                dp[i] ++;
            }
        }
    }

    FOR (i, 1, n) ans += SZ[scc[i]] - 1;
    cout << ans << "\n";
    return 0;
}