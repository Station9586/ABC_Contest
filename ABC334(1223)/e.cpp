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

template<class T> constexpr T fld (const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }
template<class T> constexpr T cld (const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }

using namespace std;

using i64 = long long;
using u64 = unsigned long long;

template<const int mod>
struct Modint {
    int x;
    
    Modint () : x(0) {}
    Modint (i64 x) : x(get(x % mod)) {}
    
    explicit operator int() const {
        return x;
    }
    
    int get(int x) const {
        if (x < 0) x += mod;
        if (x >= mod) x -= mod;
        return x;
    }
    
    Modint& operator += (const Modint rhs) {
        x = get(x + rhs.x);
        return *this;
    }
    
    Modint& operator -= (const Modint rhs) {
        x = get(x - rhs.x);
        return *this;
    }
    
    Modint& operator *= (const Modint rhs) {
        x = (i64)x * rhs.x % mod;
        return *this;
    }
    
    Modint& operator /= (const Modint rhs) {
        return *this *= rhs.inv();
    }
    
    friend Modint operator + (Modint x, const Modint y) {
        return x += y;
    }
    
    friend Modint operator - (Modint x, const Modint y) {
        return x -= y;
    }
    
    friend Modint operator * (Modint x, const Modint y) {
        return x *= y;
    }
    
    friend Modint operator / (Modint x, const Modint y) {
        return x /= y;
    }
    
    Modint operator +() const {
        return *this;
    }
    
    Modint operator -() const {
        return Modint() - *this;
    }
    
    Modint& operator ++() {
        if (++x == mod) x = 0;
        return *this;
    }
    
    Modint& operator --() {
        if (x-- == 0) x = mod - 1;
        return *this;
    }
    
    Modint operator ++(int) {
        Modint res = *this;
        ++*this;
        return res;
    }
    
    Modint operator --(int) {
        Modint res = *this;
        --*this;
        return res;
    }
    
    Modint pow(i64 n) const {
        assert(n >= 0);
        Modint res = 1, x = *this;
        while (n) {
            if (n & 1) res *= x;
            x *= x; n >>= 1;
        }
        return res;
    }
    
    Modint inv() const {
        assert(x != 0);
        return pow(mod - 2);
    }
    
    friend bool operator == (Modint x, Modint y) {
        return x.x == y.x;
    }
    
    friend bool operator != (Modint x, Modint y) {
        return x.x != y.x;
    }
    
    friend bool operator < (Modint x, Modint y) {
        return x.x < y.x;
    }
    
    friend bool operator <= (Modint x, Modint y) {
        return x.x <= y.x;
    }
    
    friend bool operator > (Modint x, Modint y) {
        return x.x > y.x;
    }
    
    friend bool operator >= (Modint x, Modint y) {
        return x.x >= y.x;
    }
    
    friend std::istream &operator >> (std::istream &is, Modint &rhs) {
        i64 x;
        is >> x;
        rhs = Modint(x);
        return is;
    }
    
    friend std::ostream &operator << (std::ostream &os, Modint rhs) {
        return os << rhs.x;
    }
};

using mint = Modint<998244353>;

const int mxN = 1e6 + 10;
int n, m;
mint ans = 0;
vector<string> gp(1010);

int p[mxN];

int Find (int a) {
    if (p[a] == a) return a;
    return p[a] = Find(p[a]);
}

void Union (int a, int b) {
    p[Find(a)] = Find(b);
}

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i ++) cin >> gp[i];
    for (int i = 0; i < n * m; i ++) p[i] = i;

    mint sum = 0;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            if (gp[i][j] == '#') {
                if (i + 1 < n and gp[i + 1][j] == '#') 
                    Union(i * m + j, (i + 1) * m + j);
                if (j + 1 < m and gp[i][j + 1] == '#') 
                    Union(i * m + j, i * m + (j + 1));
            }else sum ++;
        }
    }

    mint cnt = 0;
    for (int i = 0; i < n * m; i ++) {
        if (gp[i / m][i % m] == '#' and Find(i) == i) cnt ++;
    }

    mint cal = 0;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            if (gp[i][j] == '#') continue;
            set<int> rcd;
            for (int k = 0; k < 4; k ++) {
                int x = i + dx[k], y = j + dy[k];
                if ((x >= 0 and x < n) and (y >= 0 and y < m)) {
                    if (gp[x][y] == '#') rcd.insert(Find(x * m + y));
                }
            }
            cal += (cnt - (mint)rcd.size() + 1);
        }
    }

    ans = cal / sum;
    cout << ans << "\n";
    return 0;
}