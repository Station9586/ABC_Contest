#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

template<class T, class U> std::istream& operator >> (std::istream& in, std::pair<T, U>& p) { in >> p.first >> p.second; return in; }
template<class T, size_t N> std::istream& operator >> (std::istream& in, std::array<T, N>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::istream& operator >> (std::istream& in, std::vector<T>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::ostream& operator << (std::ostream& out, std::vector<T>& a) { for (T x: a) out << x << " "; return out; }

using namespace std;


int n, a, b;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> a >> b;
    vector<ll> v(n);
    cin >> v;
    for (int i = 0; i < n; i ++) v[i] %= (a + b);
    sort(all(v));

    ll mx = 0;
    for (int i = 0; i < n; i ++) 
        mx = max(mx, v[i + 1] - v[i] - 1);

    if (mx >= b) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}