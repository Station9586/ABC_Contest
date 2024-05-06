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

int n;
int num[mxN];

vi v;
vi gp[mxN];

int dis[mxN];
int vis[mxN];

vi color;

int mp[mxN];
int idx = 2;

void dfs (int a, int pre) {
    dis[a] = 1;
    for (int i: gp[a]) {
        if (i == pre) continue;
        color.emplace_back(num[i]);
        mp[i] = idx ++;
        dfs(i, a);
        dis[a] += dis[i];
    }
}

inline int id (int a) { return lower_bound(all(v), a) - v.begin() + 1; }

int rcd[mxN], nxt[mxN], t[mxN];

struct Node {
    int num;
    Node *lch, *rch;
    Node () {}
};

Node *st[mxN];
int ptr = 0;
Node ret[mxN * 40];

Node *new_Node (int a) {
    ret[ptr].num = a;
    return &ret[ptr ++];
}

Node *new_Node (Node *_l, Node *_r) {
    ret[ptr].lch = _l;
    ret[ptr].rch = _r;
    ret[ptr].num = 0;
    if (_l != nullptr) ret[ptr].num += ret[ptr].lch->num;
    if (_r != nullptr) ret[ptr].num += ret[ptr].rch->num;
    return &ret[ptr ++];
}

Node *build (int L, int R) {
    if (L == R) return new_Node(t[L]);
    int mid = (L + R) >> 1;
    return new_Node(build(L, mid), build(mid + 1, R));
}

Node *modify (Node *st, int L, int R, int pos, int x) {
    if (L == R) return new_Node(x);
    int mid = (L + R) >> 1;
    if (pos <= mid) return new_Node(modify(st->lch, L, mid, pos, x), st->rch);
    else return new_Node(st->lch, modify(st->rch, mid + 1, R, pos, x));
}

int query (Node *st, int L, int R, int l, int r) {
    if (l > R or r < L) return 0;
    if (l <= L and R <= r) return st->num;
    int mid = (L + R) >> 1;
    return query(st->lch, L, mid, l, r) + query(st->rch, mid + 1, R, l, r);
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> num[i];
        v.emplace_back(num[i]);
    }
    v = sort_unique(v);

    int a, b;
    for (int i = 1; i < n; i ++) {
        cin >> a >> b;
        gp[a].pb(b);
        gp[b].pb(a);
    }

    color.emplace_back(0);
    color.emplace_back(num[1]);
    mp[1] = 1;

    dfs(1, -1);

    for (int i = 1; i <= n; i ++) 
        color[i] = id(color[i]);

    for (int i = n; i > 0; i --) {
        nxt[i] = rcd[color[i]];
        rcd[color[i]] = i;
    }

    memset(rcd, 0, sizeof(rcd));

    for (int i = 1; i <= n; i ++) {
        if (!rcd[color[i]]) t[i] = 1;
        rcd[color[i]] = 1;
    }

    st[1] = build(1, n);
    for (int i = 2; i <= n; i ++) {
        st[i] = modify(st[i - 1], 1, n, i - 1, 0);
        st[i] = modify(st[i], 1, n, nxt[i - 1], 1);
    }
    for (int i = 1; i <= n; i ++) 
        cout << query(st[mp[i]], 1, n, mp[i], mp[i] + dis[i] - 1) << " \n"[i == n];
    return 0;
}