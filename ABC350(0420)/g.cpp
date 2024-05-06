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

using namespace std;


const int mod = 998244353;
const int mxN = 1e5 + 10;

int p[mxN];
ll SIZE[mxN];
int par[mxN];

vi gp[mxN];
int Find (int a) {
    if (p[a] == a) return a;
    return p[a] = Find(p[a]);
}

void Union (int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b) return;
    if (SIZE[a] < SIZE[b]) swap(a, b);
    SIZE[a] += SIZE[b];
    p[b] = a;
}

int n, q;
ll ans = 0;

void dfs (int a, int pre) {
    par[a] = pre;
    for (int i: gp[a]) {
        if (i == pre) continue;
        dfs(i, a);
    }
}

void add_path (int a, int b) {
    if (SIZE[Find(a)] > SIZE[Find(b)])
        swap(a, b);
    dfs(a, b);
    Union(a, b);
    gp[a].pb(b);
    gp[b].pb(a);
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q;
    memset(par, -1, sizeof(par));
    FOR (i, 0, n) {
        p[i] = i;
        SIZE[i] = 1;
    }
    ll a, b, c;
    while (q --) {
        bool found = false;
        cin >> a >> b >> c;
        ll op = 1 + (a * (1 + ans) % mod) % 2;
        ll u = 1 + (b * (1 + ans) % mod) % n;
        ll v = 1 + (c * (1 + ans) % mod) % n;
        if (op == 1) add_path(u, v);
        else if (op == 2) {
            // debug(par[u], par[v]);
            if (par[u] == par[v] and par[u] != -1 and !found) {
                found = true;
                ans = par[u];
            }
            if (par[u] != -1 and !found) {
                ll mid = par[u];
                if (par[mid] == v) {
                    found = true;
                    ans = mid;
                }
            }
            if (par[v] != -1 and !found) {
                ll mid = par[v];
                if (par[mid] == u) {
                    found = true;
                    ans = mid;
                }
            }
            if (!found) ans = 0;
            cout << ans << "\n";
        }
    }
    return 0;
}