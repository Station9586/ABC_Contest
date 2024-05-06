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

const int mxN = 2e5 + 10;

int n, q;

ll num[mxN];

struct Node {
    ll val, tag;
    Node *lch, *rch;
    Node () {
        val = tag = 0;
        lch = rch = nullptr;
    }
    void pull () { val = lch->val + rch->val; }
};

Node *new_Node () {
    static int ptr = 0;
    static Node ret[mxN << 2];
    return &ret[ptr ++];
}

Node *build (int L, int R) {
    Node *st = new_Node();
    if (L == R) {
        st->val = num[L];
        return st;
    }
    int mid = (L + R) >> 1;
    st->lch = build(L, mid);
    st->rch = build(mid + 1, R);
    st->pull();
    return st;
}

inline void apply (Node *st, int L, int R, ll x) {
    st->val += (R - L + 1) * x;
    st->tag += x;
}

inline void push (Node *st, int L, int R) {
    int mid = (L + R) >> 1;
    if (st->tag) {
        apply(st->lch, L, mid, st->tag);
        apply(st->rch, mid + 1, R, st->tag);
        st->tag = 0;
    }
}

void update (Node *st, int L, int R, int l, int r, ll x) {
    if (l > R or r < L) return;
    if (l <= L and R <= r) {
        apply(st, L, R, x);
        return;
    }
    push(st, L, R);
    int mid = (L + R) >> 1;
    update(st->lch, L, mid, l, r, x);
    update(st->rch, mid + 1, R, l, r, x);
    st->pull();
}

ll query (Node *st, int L, int R, int l, int r) {
    if (l > R or r < L) return 0;
    if (l <= L and R <= r) return st->val;
    push(st, L, R);
    int mid = (L + R) >> 1;
    return query(st->lch, L, mid, l, r) + query(st->rch, mid + 1, R, l, r);
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) cin >> num[i];
    Node *st = build(1, n);
    int p;
    while (q --) {
        cin >> p;
        p ++;
        ll x = query(st, 1, n, p, p);
        update(st, 1, n, p, p, -x);
        update(st, 1, n, 1, n, x / n);
        x %= n;
        if (p + x >= n) {
            update(st, 1, n, p + 1, n, 1);
            update(st, 1, n, 1, p + x - n, 1);
        }else update(st, 1, n, p + 1, p + x, 1);
    }
    for (int i = 1; i <= n; i ++) cout << query(st, 1, n, i, i) << " \n"[i == n];
    return 0;
}