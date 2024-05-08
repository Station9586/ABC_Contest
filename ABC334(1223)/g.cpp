#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())
#define lowbit(x) (x) & (-x)

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

template<typename... T> void read (T&... args) { ((std::cin >> args), ...); }
template<typename... T> void put (T&&... args) { ((std::cout << args << " "), ...); }
template<typename... T> void print (T&&... args) { ((std::cout << args << " "), ...); std::cout << "\n"; }

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
template<typename T> inline T __lg (T __n) { T __k; for (__k = 0; __n != 0; __n >>= 1) ++ __k; return __k - 1; }

using namespace std;

const int mxN = 2e5 + 10;
const int H = 25;

int n, q;

int to[H + 1][mxN], cg[mxN], csiz[mxN], h[mxN], pos[mxN];
bool vis[mxN], cs[mxN];

int Find (int pos, int k) {
    if (k == 0) return pos;
    return Find(to[__lg(k & -k)][pos], k - (k & -k));
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q;

    for (int i = 1; i <= n; i ++) cin >> to[0][i];

    int cl = 0, cz;
    for (int i = 1; i <= n; i ++) {
        if (vis[i]) continue;
        stack<int> st;
        int now = i;
        while (true) {
            vis[now] = 1;
            st.push(now);
            now = to[0][now];
            if (cs[now]) {
                int l = 0;
                while (!st.empty()) {
                    h[st.top()] = ++ l;
                    cg[st.top()] = cg[now];
                    st.pop();
                }
                break;
            }
            if (h[now]) {
                int l = h[now];
                while (!st.empty()) {
                    h[st.top()] = ++ l;
                    cg[st.top()] = cg[now];
                    st.pop();
                }
                break;
            }
            if (vis[now] and h[now] == 0) {
                stack<int> cyc;
                while (true) {
                    cyc.push(st.top());
                    st.pop();
                    if (cyc.top() == now) break;
                }
                cl ++;
                cz = sz(cyc);
                int p = 0;
                while (!cyc.empty()) {
                    cg[cyc.top()] = cl;
                    csiz[cyc.top()] = cz;
                    cs[cyc.top()] = 1;
                    pos[cyc.top()] = p ++;
                    cyc.pop();
                }
                int l = 0;
                while (!st.empty()) {
                    h[st.top()] = ++ l;
                    cg[st.top()] = cg[now];
                    st.pop();
                }
                break;
            }
        }
    }
    
    for (int i = 1; i <= H; i ++) {
        for (int j = 1; j <= n; j ++) {
            to[i][j] = to[i - 1][to[i - 1][j]];
        }
    }

    while (q --) {
        int a, b;
        cin >> a >> b;
        if (h[a] < h[b]) {
            cout << "-1\n";
            continue;
        }
        if (cg[a] != cg[b]) {
            cout << "-1\n";
            continue;
        }
        int ans = h[a] - h[b];
        a = Find(a, h[a] - h[b]);
        if (h[b]) {
            if (a != b) cout << "-1\n";
            else cout << ans << "\n";
            continue;
        }
        cout << (ans + (pos[b] + csiz[b] - pos[a]) % csiz[b]) << "\n";
    }
    return 0;
}