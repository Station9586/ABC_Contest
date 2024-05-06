// E.cpp another solution
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

const int mxN = 1e5 + 10;

int n;
vi gp[mxN];

ll sub[mxN], c[mxN], dis[mxN];
ll N, ans;

ll cnt (int a, int pre) {
    sub[a] = c[a];
    for (int i: gp[a]) {
        if (i == pre) continue;
        sub[a] += cnt(i, a);
    }
    return sub[a];
}

int Find (int a, int pre) {
    for (int i: gp[a]) {
        if (i == pre) continue;
        if (sub[i] > N / 2) return Find(i, a);
    }
    return a;
}

void dfs (int a, int pre, ll d) { // Count depth
    dis[a] = d;
    for (int i: gp[a]) {
        if (i == pre) continue;
        dfs(i, a, d + 1);
    }
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    int a, b;
    FOR (i, 1, n - 1) {
        cin >> a >> b;
        gp[a].pb(b);
        gp[b].pb(a);
    }

    FOR (i, 1, n) cin >> c[i];
    N = accumulate(c + 1, c + n + 1, 0ll);
    cnt(1, 0);

    int centroid = Find(1, 0);
    dfs(centroid, 0, 0);
    for (int i = 1; i <= n; i ++) 
        ans += dis[i] * c[i];

    cout << ans << "\n";
    return 0;
}