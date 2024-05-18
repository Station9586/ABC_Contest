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

using namespace std;

using tp = array<int, 3>;

int n;

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    vector<tp> cards(n);
    vi v;
    REP (i, n) {
        cin >> cards[i][0] >> cards[i][1];
        cards[i][2] = i + 1;
        v.pb(cards[i][0]);
    }

    sort(all(cards), [] (tp a, tp b) { return a[1] > b[1]; });
    v = sort_unique(v);
    auto id = [&] (int a) { return lower_bound(all(v), a) - v.begin() + 1; };

    REP (i, n) cards[i][0] = id(cards[i][0]);

    int mx = n;
    set<int> remove;
    set<int> rec;
    FOR (i, 1, n) rec.insert(i);
    REP (i, n - 1) {
        if (cards[i][0] < mx) {
            remove.insert(cards[i][2]);
            rec.erase(rec.find(cards[i][0]));
        }
        else {
            rec.erase(rec.find(mx));
            mx = *rec.rbegin();
        }
    }

    cout << n - sz(remove) << "\n";
    FOR (i, 1, n) {
        if (remove.count(i)) continue;
        cout << i << " ";
    }
    cout << "\n";

    return 0;
}