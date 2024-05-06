#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())
#define FOR(i, a, b) for (int i = a; i <= b; i ++)
#define REP(i, a, b) for (int i = a; i < b; i ++)
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
template<class T> std::ostream& operator << (std::ostream& out, std::vector<T>& a) { for (T x: a) out << x << " "; out << "\n"; return out; }

template<typename... T> void read (T&... args) { ((std::cin >> args), ...); }
template<typename... T> void put (T&&... args) { ((std::cout << args << " "), ...); }
template<typename... T> void print (T&&... args) { ((std::cout << args << " "), ...); std::cout << "\n"; }

template<class T> constexpr T fld (const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }
template<class T> constexpr T cld (const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }
template<typename T> inline T __lg (T __n) { T __k; for (__k = 0; __n != 0; __n >>= 1) ++ __k; return __k - 1; }

#ifdef LOCAL
#define debug(HEHE...) std::cout << "[" << #HEHE << "] : ", dout(HEHE)
void dout() { std::cout << '\n'; }
template<typename T, typename...U> 
void dout(T t, U...u) { std::cout << t << (sizeof...(u) ? ", " : ""), dout(u...); }
#else
#define debug(...) 7122
#endif

using namespace std;

const int mxN = 1e5 + 10;

int n;

vi gp[mxN];

vector<ll> f(mxN), sub(mxN);
vi c(mxN);

vector<ll> ans;

void dfs (int a, int pre) {
    sub[a] = c[a];
    for (int i: gp[a]) {
        if (i == pre) continue;
        dfs(i, a);
        sub[a] += sub[i];
        f[a] += f[i] + sub[i];
    }
}

void dfs2 (int a, int pre) {
    ans[a - 1] = f[a];
    debug(a, f[a]);
    for (int i: gp[a]) {
        if (i == pre) continue;
        f[a] -= f[i] + sub[i];
        sub[a] -= sub[i];
        sub[i] += sub[a];
        f[i] += f[a] + sub[a];
        dfs2(i, a);
        f[i] -= f[a] + sub[a];
        sub[i] -= sub[a];
        sub[a] += sub[i];
        f[a] += f[i] + sub[i];
    }
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    ans.resize(n);
    int a, b;
    REP (i, 0, n - 1) {
        cin >> a >> b;
        gp[a].pb(b);
        gp[b].pb(a);
    }
    
    FOR (i, 1, n) cin >> c[i];
    dfs(1, 0);
    dfs2(1, 0);

    cout << *min_element(all(ans)) << "\n";
    return 0;
}