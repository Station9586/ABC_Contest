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
#define debug(HEHE...) std::cout << "[" << #HEHE << "] : ", dout(HEHE)
void dout() { std::cout << '\n'; }
template<typename T, typename...U> 
void dout(T t, U...u) { std::cout << t << (sizeof...(u) ? ", " : ""), dout(u...); }
#else
#define debug(...) 7122
#endif
using namespace std;

int n;
const ll mod = 1e8;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    vector<ll> v(n);
    cin >> v;
    sort(all(v));

    ll cnt = 0;

    for (ll i: v) {
        ll remain = mod - i;
        int pos = lower_bound(all(v), remain) - v.begin();
        debug(pos, n - pos, i, remain);
        cnt += n - pos;
        if (i >= remain) cnt --;
    }
    cnt /= 2;
    ll sum = accumulate(all(v), 0ll);
    sum *= (n - 1);
    cout << sum - cnt * mod << "\n";
    return 0;
}