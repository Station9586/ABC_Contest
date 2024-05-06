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

#ifdef LOCAL
#define debug(HEHE...) std::cout << "[" << #HEHE << "] : ", dout(HEHE)
void dout() { std::cout << '\n'; }
template<typename T, typename...U> 
void dout(T t, U...u) { std::cout << t << (sizeof...(u) ? ", " : ""), dout(u...); }
#else
#define debug(...) 7122
#endif

using namespace std;

const int mxN = 2e5 + 10;
using tp = array<int, 3>;
int n, m;

vector<tp> edges;

int p[mxN];
ll SIZE[mxN];

int Find (int a) {
    if (p[a] == a) return a;
    return p[a] = Find(p[a]);
}

void Union (int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b) return;
    if (SIZE[a] < SIZE[b]) swap(a, b);
    SIZE[a] += SIZE[b];
    p[b] = a;
}

bool same (int a, int b) { return Find(a) == Find(b); }

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    REP (i, n + 1) {
        p[i] = i;
        SIZE[i] = 1;
    }
    REP (i, m) {
        int k, c;
        cin >> k >> c;
        vi a(k);
        cin >> a;
        FOR (j, 1, k - 1) edges.pb({c, a[0], a[j]});
    }
    sort(all(edges));
    ll ans = 0;
    int cnt = 1;
    for (auto [c, u, v]: edges) {
        if (!same(u, v)) {
            ans += c;
            Union(u, v);
            cnt ++;
        }
    }
    debug(SIZE[1], n, ans, cnt);
    if (cnt == n) cout << ans << "\n";
    else cout << "-1\n";
    return 0;
}