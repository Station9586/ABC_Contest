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

using namespace std;

const ll INF = 1e18;
const int mxN = 4e5 + 10;

int n, k;
ll val[mxN], val2[mxN];

vi vis(mxN, 0);
vector<ll> seq;

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    vector<ll> num(k);
    for (int i = 0; i < k; i ++) {
        cin >> num[i];
        vis[i] = 1;
    }
    for (int i = 1; i <= n; i ++) {
        if (vis[i]) seq.pb(i);
        else {
            seq.pb(i);
            seq.pb(i);
        }
    }
    int len = sz(seq);
    if (!(len & 1)) {
        ll ans = 0;
        for (int i = 1; i < len; i += 2) 
            ans += seq[i] - seq[i - 1];
        cout << ans << "\n";
        return 0;
    }
    for (int i = 1; i < len; i += 2) val[i] = seq[i] - seq[i - 1];
    for (int i = 3; i < len; i += 2) val[i] += val[i - 2];
    for (int i = len - 1; i > 0; i -= 2) val2[i - 1] = seq[i] - seq[i - 1];
    for (int i = len - 3; i > 0; i -= 2) val2[i - 1] += val2[i + 1];
    ll ans = INF;
    for (int i = 1; i < len; i += 2) chmin(ans, val[i] + val2[i + 2]);
    cout << ans << "\n";
    return 0;
}