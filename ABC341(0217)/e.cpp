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

int n, q;
string s;

struct Node {
    int mx[2];
    int l[2], r[2];
    int len;
    Node *lch, *rch;
    int tag = 0;
    Node () {
        for (int i = 0; i < 2; i ++) mx[i] = l[i] = r[i] = 0;
        len = 0;
        lch = rch = nullptr;
        tag = 0;
    }

    Node (char c) {
        for (int i = 0; i < 2; i ++) mx[i] = l[i] = r[i] = (c == '0' + i);
        len = 1;
    }
    
    void rev () {
        swap(mx[0], mx[1]);
        swap(l[0], l[1]);
        swap(r[0], r[1]);
    }

    friend Node operator + (const Node &l, const Node &r) {
        Node ret;
        for (int i = 0; i < 2; i ++) {
            ret.l[i] = l.l[i] + (l.l[i] == l.len? r.l[i]: 0);
            ret.r[i] = r.r[i] + (r.r[i] == r.len? l.r[i]: 0);
            ret.mx[i] = max({l.mx[i], r.mx[i], l.r[i] + r.l[i]});
        }
        ret.len = l.len + r.len;
        return ret;
    }

    void pull () {
        for (int i = 0; i < 2; i ++) {
            l[i] = lch->l[i] + ((lch->l[i] == lch->len)? rch->l[i]: 0);
            r[i] = rch->r[i] + ((rch->r[i] == rch->len)? lch->r[i]: 0);
            mx[i] = max({lch->mx[i], rch->mx[i], lch->r[i] + rch->l[i]});
        }
        len = lch->len + rch->len;
    }
};

Node *build (int L, int R) {
    Node *st = new Node();
    if (L == R) {
        *st = Node(s[L - 1]);
        return st;
    }
    int mid = (L + R) >> 1;
    st->lch = build(L, mid);
    st->rch = build(mid + 1, R);
    st->pull();
    return st;
}

void apply (Node *st) {
    st->rev();
    st->tag ^= 1;
}

void push (Node *st) {
    if (st->tag) {
        apply(st->lch);
        apply(st->rch);
        st->tag = 0;
    }
}

void update (Node *st, int L, int R, int l, int r) {
    if (l > R or r < L) return;
    if (l <= L and R <= r) {
        apply(st);
        return;
    }
    push(st);
    int mid = (L + R) >> 1;
    update(st->lch, L, mid, l, r);
    update(st->rch, mid + 1, R, l, r);
    st->pull();
}

Node query (Node *st, int L, int R, int l, int r) {
    if (l > R or r < L) return {};
    if (l <= L and R <= r) return *st;
    push(st);
    int mid = (L + R) >> 1;
    return query(st->lch, L, mid, l, r) + query(st->rch, mid + 1, R, l, r);
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q;
    cin >> s;
    Node *st = build(1, n);
    int op, a, b;
    while (q --) {
        cin >> op >> a >> b;
        if (op == 1) update(st, 1, n, a, b);
        else if (op == 2) {
            Node qry = query(st, 1, n, a, b);
            int _a = qry.mx[0], _b = qry.mx[1];
            if ((_a == 0 and _b == 1) or (_a == 1 and _b == 0) or (_a == 1 and _b == 1)) cout << "Yes\n";
            else cout << "No\n";
        }
     }
    return 0;
}