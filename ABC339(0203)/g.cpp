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

vector<vi> mst;
vector<vector<ll>> prefix;

void build (vi &num) {
    mst.resize(n << 1), prefix.resize(n << 1);
    for (int i = 0; i < n; i ++) {
        mst[i + n] = {num[i]};
        prefix[i + n] = {0, num[i]};
    }
    for (int i = n - 1; i >= 0; i --) {
        merge(all(mst[i << 1]), all(mst[i << 1 | 1]), back_inserter(mst[i]));
        prefix[i].reserve(sz(mst[i]) + 1);
        prefix[i].emplace_back(0);
        for (int j = 0; j < sz(mst[i]); j ++) 
            prefix[i].emplace_back(prefix[i].back() + mst[i][j]);
    }
}

ll query (int L, int R, int x) {
    ll ret = 0;
    for (L += n, R += n; L <= R; L >>= 1, R >>= 1) {
        if (L & 1) {
            int p = upper_bound(all(mst[L]), x) - mst[L].begin();
            ret += prefix[L][p];
            L ++;    
        }
        if (~R & 1) {
            int p = upper_bound(all(mst[R]), x) - mst[R].begin();
            ret += prefix[R][p];
            R --;
        }
    }
    return ret;
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    vi num(n);
    cin >> num;

    build(num);

    cin >> q;
    ll key = 0;
    ll a, b, r;

    while (q --) {
        cin >> a >> b >> r;
        a ^= key, b ^= key, r ^= key;
        key = query(a - 1, b - 1, r);
        cout << key << "\n";
    }
    return 0;
}