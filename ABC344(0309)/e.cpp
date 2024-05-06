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
template<class T> std::vector<T> sort_unique (std::vector<T> v) { std::sort(aint(v)), v.erase(std::unique(aint(v)), v.end()); return v; }

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

const int mxN = 1e6 + 10;

struct Node {
    int nxt, pre;
    bool ok;
    Node () {
        nxt = pre = 0;
        ok = false;
    }
} d[mxN]; // Doubly Linked List

int n, q, p;
int total;

int s[mxN << 1];
map<int, int> mp;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    int input;
    for (int i = 1; i <= n; i ++) {
        cin >> input;
        mp[input] = i;
        d[i].pre = i - 1;
        d[i].nxt = i + 1;
        d[i].ok = 1;
        s[i] = input;
    }

    total = n;
    d[n].nxt = 0;
    cin >> q;
    int op, a, b, x;
    while (q --) {
        cin >> op;
        if (op == 1) {
            cin >> a >> b;
            total ++;
            x = mp[a];
            mp[b] = total;
            d[total].ok = 1;
            d[total].pre = x;
            d[total].nxt = d[x].nxt;
            s[total] = b;
            d[d[x].nxt].pre = total;
            d[x].nxt = total;
        }else if (op == 2) {
            cin >> a;
            x = mp[a];
            d[d[x].pre].nxt = d[x].nxt;
            d[d[x].nxt].pre = d[x].pre;
            d[x].nxt = d[x].pre = 0;
            d[x].ok = 0;
            mp[a] = 0;
        }
    }
    for (int i = 1; i <= total; i ++) {
        if (d[i].ok) {
            p = i;
            break;
        }
    }
    while (d[p].pre) p = d[p].pre;
    while (p) {
        cout << s[p] << " \n"[d[p].nxt == 0];
        p = d[p].nxt;
    }
    return 0;
}
