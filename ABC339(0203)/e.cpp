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

const int mxN = 5e5 + 10;
int n, d;

ll num[mxN];

struct Node {
    ll mx;
    Node *lch, *rch;
    Node () {
        mx = 0;
        lch = rch = nullptr;
    }
    void pull () { mx = max(lch->mx, rch->mx); }
};

Node *build (int L, int R) {
    Node *st = new Node();
    if (L == R) {
        st->mx = 0;
        return st;
    }
    int mid = (L + R) >> 1;
    st->lch = build(L, mid);
    st->rch = build(mid + 1, R);
    st->pull();
    return st;
}

void update (Node *st, int L, int R, int pos, ll x) {
    if (L == R) {
        st->mx = x + 1;
        return;
    }
    int mid = (L + R) >> 1;
    if (pos <= mid) update(st->lch, L, mid, pos, x);
    else update(st->rch, mid + 1, R, pos, x);
    st->pull();
}

ll query (Node *st, int L, int R, int l, int r) {
    if (l > R or r < L) return 0;
    if (l <= L and R <= r) return st->mx;
    int mid = (L + R) >> 1;
    return max(query(st->lch, L, mid, l, r), query(st->rch, mid + 1, R, l, r));
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> d;
    for (int i = 1; i <= n; i ++) cin >> num[i];
    Node *st = build(1, mxN);
    for (int i = 1; i <= n; i ++) {
        ll a = max(num[i] - d, 0ll);
        ll b = min(num[i] + d, (ll)mxN);
        update(st, 1, mxN, num[i], query(st, 1, mxN, a, b));
    }
    cout << st->mx << "\n";
    return 0;
}