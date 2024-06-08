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

#ifdef LOCAL
#define debug(QQ...) std::cout << "[" << #QQ << "] : ", dout(QQ)
void dout() { std::cout << '\n'; }
template<typename T, typename...U> 
void dout(T t, U...u) { std::cout << t << (sizeof...(u) ? ", " : ""), dout(u...); }
#else
#define debug(...) 7122
#endif

using namespace std;

const int mxN = 2e5 + 10;
const ll mod = 998244353;


struct Node {
    ll a, b;
    Node *lch, *rch;
    ll prod;
    ll tag_a, tag_b;
    ll sum_a, sum_b;
    Node () {
        lch = rch = nullptr;
        tag_a = tag_b = 0;
        a = b = 0;
        prod = 0;
        sum_a = sum_b = 0;
    }

    void pull () { 
        prod = (lch->prod + rch->prod) % mod; 
        sum_a = (lch->sum_a + rch->sum_a) % mod;
        sum_b = (lch->sum_b + rch->sum_b) % mod;
    }
};

ll numa[mxN], numb[mxN];

Node *build (int L, int R) {
    Node *st = new Node();
    if (L == R) {
        st->a = st->sum_a = numa[L];
        st->b = st->sum_b = numb[L];
        st->prod = numa[L] * numb[L] % mod;
        return st;
    }
    int mid = (L + R) >> 1;
    st->lch = build(L, mid);
    st->rch = build(mid + 1, R);
    st->pull();
    return st;
}

inline void apply_a (Node *st, int L, int R, ll x) {
    st->prod += st->sum_b * x % mod;
    st->prod %= mod;
    st->sum_a += (R - L + 1) * x % mod;
    st->sum_a %= mod;
    st->tag_a += x;
    st->tag_a %= mod;
}

inline void apply_b (Node *st, int L, int R, ll x) {
    st->prod += st->sum_a * x % mod;
    st->prod %= mod;
    st->sum_b += (R - L + 1) * x % mod;
    st->sum_b %= mod;
    st->tag_b += x;
    st->tag_b %= mod;
}

inline void push (Node *st, int L, int R) {
    int mid = (L + R) >> 1;
    if (st->tag_a) {
        apply_a(st->lch, L, mid, st->tag_a);
        apply_a(st->rch, mid + 1, R, st->tag_a);
        st->tag_a = 0;
    }
    if (st->tag_b) {
        apply_b(st->lch, L, mid, st->tag_b);
        apply_b(st->rch, mid + 1, R, st->tag_b);
        st->tag_b = 0;
    }
}

void update_a (Node *st, int L, int R, int l, int r, ll x) {
    if (l > R or r < L) return;
    if (l <= L and R <= r) {
        apply_a(st, L, R, x);
        return;
    }
    push(st, L, R);
    int mid = (L + R) >> 1;
    update_a(st->lch, L, mid, l, r, x);
    update_a(st->rch, mid + 1, R, l, r, x);
    st->pull();
}

void update_b (Node *st, int L, int R, int l, int r, ll x) {
    if (l > R or r < L) return;
    if (l <= L and R <= r) {
        apply_b(st, L, R, x);
        return;
    }
    push(st, L, R);
    int mid = (L + R) >> 1;
    update_b(st->lch, L, mid, l, r, x);
    update_b(st->rch, mid + 1, R, l, r, x);
    st->pull();
}

ll query (Node *st, int L, int R, int l, int r) {
    if (l > R or r < L) return 0ll;
    if (l <= L and R <= r) return st->prod % mod;
    push(st, L, R);
    int mid = (L + R) >> 1;
    return (query(st->lch, L, mid, l, r) + query(st->rch, mid + 1, R, l, r)) % mod;
}

int n, q;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q;
    FOR (i, 1, n) cin >> numa[i];
    FOR (i, 1, n) cin >> numb[i];

    Node *st = build(1, n);
    int op, a, b, c;
    while (q --) {
        cin >> op;
        if (op == 1 or op == 2) {
            cin >> a >> b >> c;
            if (op == 1) update_a(st, 1, n, a, b, c);
            else if (op == 2) update_b(st, 1, n, a, b, c);
        }else if (op == 3) {
            cin >> a >> b;
            cout << query(st, 1, n, a, b) << "\n";
        }
    }
    return 0;
}