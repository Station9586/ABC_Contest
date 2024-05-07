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

vi gp[mxN];
int num[mxN];

int sub[mxN], dep[mxN];

int par[mxN];

int heavy[mxN], head[mxN], id[mxN];

void dfs (int a, int pre) {
    sub[a] = 1;
    int mx = -1;

    for (int i: gp[a]) {
        if (i == pre) continue;
        par[i] = a;
        dep[i] = dep[a] + 1;
        dfs(i, a);
        sub[a] += sub[i];
        if (chmax(mx, sub[i])) heavy[a] = i;
    }
}

int idx = 1;


int st[mxN * 10];

void update (int p, int x) {
    p += n;
    st[p] = x;
    p >>= 1;
    while (p > 1) {
        st[p] = max(st[p << 1], st[p << 1 | 1]);
        p >>= 1;
    }
}

int query (int a, int b) {
    a += n, b += n;
    int ret = -1;
    while (a <= b) {
        if (a & 1) ret = max(ret, st[a ++]);
        if (~b & 1) ret = max(ret, st[b --]);
        a >>= 1, b >>= 1;
    }
    return ret;
}

void hld (int a, int h) {
    head[a] = h;
    id[a] = idx ++;
    update(id[a], num[a]);
    if (heavy[a]) hld(heavy[a], h);
    for (int i: gp[a]) {
        if (i != par[i] && i != heavy[a]) 
            hld(i, i);
    }
}

int Search (int a, int b) {
    int ret = 0;
    while (head[a] != head[b]) {
        if (dep[a] > dep[b]) swap(a, b);
        ret = max(ret, query(id[head[b]], id[b]));
    }
    if (dep[a] > dep[b]) swap(a, b);
    ret = max(ret, query(id[a], id[b]));
    return ret;
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) 
        cin >> num[i];

    int a, b;
    for (int i = 1; i < n; i ++) {
        cin >> a >> b;
        gp[a].emplace_back(b);
        gp[b].emplace_back(a);
    }

    dfs(1, 0);
    hld(1, 1);
    int op;
    while (q --) {
        cin >> op >> a >> b;
        if (op == 1) update(id[a], b);
        else if (op == 2) cout << Search(a, b) << "\n";
    }
    return 0;
}