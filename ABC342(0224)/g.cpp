#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<ll, ll> pi;

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

const int mxN = 2e5 + 10;

int n, q;
ll num[mxN];
bool vis[mxN];

struct ST {
    ll low[mxN << 2], high[mxN << 2];
    max_heap<pi> pq[mxN << 2];

    void build (ll x, ll L, ll R) {
        low[x] = L, high[x] = R;
        if (L == R) return;
        ll mid = (L + R) >> 1;
        build(x << 1, L, mid);
        build(x << 1 | 1, mid + 1, R);
        return;
    }

    void update (ll x, ll L, ll R, ll v, ll t) {
        ll l = low[x], r = high[x];
        if (L <= l and r <= R) {
            pq[x].push({v, t});
            return;
        }
        ll mid = (l + r) >> 1;
        if (mid >= L) update(x << 1, L, R, v, t);
        if (mid < R) update(x << 1 | 1, L, R, v, t);
        return;
    }

    ll query (ll x, ll L) {
        ll l = low[x], r = high[x], ret = 0;
        while (!pq[x].empty()) {
            if (!vis[pq[x].top().second]) break;
            pq[x].pop();
        }
        if (!pq[x].empty()) ret = max(ret, pq[x].top().first);
        if (l == r) return ret;
        ll mid = (l + r) >> 1;
        if (mid >= L) ret = max(ret, query(x << 1, L));
        else ret = max(ret, query(x << 1 | 1, L));
        return ret;
    }
}st;

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i ++) cin >> num[i];
    cin >> q;
    st.build(1, 0, n - 1);
    ll op, l, r, v;
    for (int i = 0; i < q; i ++) {
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> v;
            l --, r --;
            st.update(1, l, r, v, i);
        }else if (op == 2) {
            cin >> l;
            l --;
            vis[l] = 1;
        }else if (op == 3) {
            cin >> l;
            l --;
            cout << max(st.query(1, l), num[l]) << "\n";
        }
    }
    return 0;
}