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

template<class T, class U> std::istream& operator >> (std::istream& in, std::pair<T, U>& p) { in >> p.first >> p.second; return in; }
template<class T, size_t N> std::istream& operator >> (std::istream& in, std::array<T, N>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::istream& operator >> (std::istream& in, std::vector<T>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::ostream& operator << (std::ostream& out, std::vector<T>& a) { for (T x: a) out << x << " "; return out; }

#ifdef LOCAL
#define debug(QQ...) std::cout << "[" << #QQ << "] : ", dout(QQ)
void dout() { std::cout << '\n'; }
template<typename T, typename...U> 
void dout(T t, U...u) { std::cout << t << (sizeof...(u) ? ", " : ""), dout(u...); }
#else
#define debug(...) 7122
#endif

using namespace std;

int T;

void solve () {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    int mx = 0;

    auto cal = [&] (vi a) {
        vi lis;
        vi ret(n);
        REP (i, n) {
            if (lis.empty() or lis.back() < a[i]) {
                lis.pb(a[i]);
                ret[i] = sz(lis);
            }else {
                ret[i] = lower_bound(all(lis), a[i]) - lis.begin() + 1;
                lis[ret[i] - 1] = a[i];
            }
        }
        mx = sz(lis);
        debug(lis);
        return ret;
    };

    vi L = cal(a);
    reverse(all(a));
    for (int &i: a) i *= -1;
    vi R = cal(a);
    reverse(all(R));
    debug(L, R, mx);
    vi ans;
    REP (i, n) {
        if (L[i] + R[i] - 1 == mx)
            ans.pb(i + 1);
    }
    cout << sz(ans) << "\n";
    cout << ans << "\n";
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> T;
    while (T --) { solve(); }
    return 0;
}