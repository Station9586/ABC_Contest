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

template<typename T>
struct BIT {
    vector<T> bit;
    int n, offset;
    BIT () = default;
    BIT (int _n, int _offset = 3): n(_n + _offset * 2), offset(_offset) {
        bit.assign(n, 0);
    }
    void add (int p, T v) {
        for (p += offset; p < n; p += p & (-p))
            bit[p] += v;
    }
    T query (int p) {
        T ret = 0;
        for (p += offset; p > 0; p -= p & (-p))
            ret += bit[p];
        return ret; 
    }
    T query (int L, int R) { // [L, R)
        return query(R - 1) - query(L - 1);
    }
    int kth (int k) {
        int ret = 0;
        for (int i = 1 << __lg(n); i > 0; i >>= 1) 
            if (ret + i < n and bit[ret + i] < k) 
                k -= bit[ret += i];
        return ret - offset + 1;
    }
};

int n;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    vi gp[n];
    int a, b;
    for (int i = 0; i < n - 1; i ++) {
        cin >> a >> b;
        a --, b --;
        gp[a].pb(b);
        gp[b].pb(a);
    }

    vi in(n), out(n), par(n);
    int _t = 0;
    auto dfs = [&] (auto dfs, int x, int pre) -> void {
        in[x] = _t ++;
        par[x] = pre;
        for (int i: gp[x]) 
            if (i != pre)
                dfs(dfs, i, x);
        out[x] = _t ++;
    };

    dfs(dfs, 0, -1);

    vector<ll> down(n);
    BIT<int> bit(n << 1);
    ll total = 0;
    bit.add(in[0], 1);
    cout << "in: " << in << ", out: " << out << "\n";
    for (int i = 1; i < n; i ++) {
        for (int j: gp[i]) {
            if (j == par[i]) continue;
            down[j] += i - bit.query(in[j], out[j] + 1);
        }
        int res = bit.query(in[i], out[i] + 1);
        total += res;
        down[i] -= res;
        bit.add(in[i], 1);
    }

    auto dfs2 = [&] (auto dfs2, int a, int pre) -> void {
        for (int i: gp[a]) {
            if (i == pre) continue;
            down[i] += down[a];
            dfs2(dfs2, i, a);
        }
    };

    dfs2(dfs2, 0, -1);
    cout << "down: " << down << "\n";
    cout << "total: " << total << "\n";
    for (int i = 0; i < n; i ++) 
        cout << total + down[i] + i << " \n"[i == n - 1];
    return 0;
}