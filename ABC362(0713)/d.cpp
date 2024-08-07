#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())
#define FOR(i, a, b) for (int i = a; i <= b; i ++)
#define REP(i, b) for (int i = 0; i < b; i ++)
#define IFOR(i, a, b) for (int i = b - 1; i >= a; i --) 

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<ll, int> pi;

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
const ll INF = 1e18;

struct Node {
    int v;
    ll w;
    Node (int _v, ll _w) {
        v = _v;
        w = _w;
    }
};

int n, m;
ll A[mxN];
vector<Node> gp[mxN];
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    FOR (i, 1, n) cin >> A[i];
    int a, b;
    ll c;
    REP (i, m) {
        cin >> a >> b >> c;
        gp[a].pb({b, c});
        gp[b].pb({a, c});
    }

    vector<ll> dis(mxN, INF);

    min_heap<pi> pq;
    dis[1] = A[1];
    pq.push({dis[1], 1});

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d > dis[v]) continue;
        for (auto [_v, w]: gp[v]) {
            ll now = d + w + A[_v];
            if (chmin(dis[_v], now)) 
                pq.push({now, _v});
        }
    }

    FOR (i, 2, n) cout << dis[i] << " \n"[i == n];
    return 0;
}