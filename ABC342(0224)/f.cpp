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

struct SegTree {
    ll L, R;
    max_heap<pi> pq;
    SegTree *lch, *rch;
    SegTree () {
        lch = rch = nullptr;
        L = R = 0;
        pq = max_heap<pi> ();
    }

    void build (SegTree *st, ll l, ll r) {
        if (st->lch == nullptr) st->lch = new SegTree();
        if (st->rch == nullptr) st->rch = new SegTree();
        st->L = l;
        st->R = r;
        if (l == r) return;
        ll mid = (l + r) >> 1;
        build(st->lch, l, mid);
        build(st->rch, mid + 1, r);
    }

    void update (SegTree *st, ll l, ll r, ll v, ll t) {
        if (l <= st->L and st->R <= r) {
            st->pq.push({v, t});
            return;
        }
        ll mid = (st->L + st->R) >> 1;
        if (mid >= l) update(st->lch, l, r, v, t);
        if (mid < r) update(st->rch, l, r, v, t);
        return;
    }

    ll query (SegTree *st, ll l) {
        ll ret = 0;
        while (!st->pq.empty()) {
            if (!vis[st->pq.top().second]) break;
            st->pq.pop();
        }
        if (!st->pq.empty()) ret = max(ret, st->pq.top().first);
        if (st->L == st->R) return ret;
        ll mid = (st->L + st->R) >> 1;
        if (mid >= l) ret = max(ret, query(st->lch, l));
        else ret = max(ret, query(st->rch, l));
        return ret;
    }

}*st = new SegTree();

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> num[i];
    cin >> q;
    st->build(st, 1, n);
    ll op, l, r, v;
    for (int i = 1; i <= q; i ++) {
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> v;
            st->update(st, l, r, v, i);
        }else if (op == 2) {
            cin >> l;
            vis[l] = 1;
        }else if (op == 3) {
            cin >> l;
            cout << max(st->query(st, l), num[l]) << "\n";
        }
    }
    return 0;
}