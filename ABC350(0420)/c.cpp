#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())
#define FOR(i, a, b) for (int i = a; i <= b; i ++)
#define REP(i, a, b) for (int i = a; i < b; i ++)
#define IFOR(i, a, b) for (int i = b - 1; i >= a; i --) 

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

template<class T, class U> std::istream& operator >> (std::istream& in, std::pair<T, U>& p) { in >> p.first >> p.second; return in; }
template<class T, size_t N> std::istream& operator >> (std::istream& in, std::array<T, N>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::istream& operator >> (std::istream& in, std::vector<T>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::ostream& operator << (std::ostream& out, std::vector<T>& a) { for (T x: a) out << x << " "; return out; }

using namespace std;


int n;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    vi v(n);
    cin >> v;
    vi pos(n + 1);
    vector<pi> ans;
    REP(i, 0, n) pos[v[i]] = i;
    FOR (i, 1, n) {
        if (v[i - 1] == i) continue;
        int now = i - 1;
        int cur = pos[i];
        swap(v[now], v[cur]);
        pos[v[cur]] = cur;
        pos[v[now]] = now;
        ans.pb({now + 1, cur + 1});
    }
    cout << sz(ans) << "\n";
    for (auto [a, b]: ans)
        cout << a << " " << b << "\n";
    return 0;
}