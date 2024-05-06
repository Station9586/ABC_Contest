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

const int mxN = 2e5 + 10;

int n, m, k;
vector<pi> gp[mxN];

int vis[mxN], lamp[mxN];

int cnt = 0;
vi ans;

void dfs (int a) {
    vis[a] = 1;
    for (auto [i, id] : gp[a]) {
        if (vis[i]) continue;
        dfs(i);
        if (lamp[i] == 0 and cnt < k) {
            cnt -= lamp[i] + lamp[a];
            lamp[i] ^= 1, lamp[a] ^= 1;
            cnt += lamp[i] + lamp[a];
            ans.emplace_back(id);
        }
    }
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> k;
    int a, b;
    for (int i = 1; i <= m; i ++) {
        cin >> a >> b;
        gp[a].pb({b, i});
        gp[b].pb({a, i});
    }

    for (int i = 0; i < n; i ++) {
        if (!vis[i]) 
            dfs(i);
    }

    if (cnt != k) cout << "No\n";
    else cout << "Yes\n" << sz(ans) << "\n" << ans << "\n";
    return 0;
}