#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

template<class T> std::ostream& operator << (std::ostream& out, std::vector<T> v) { for (T i: v) out << i << " "; return out; }

using namespace std;

const int mxN = 2e5 + 10;

int n;
int num[mxN];

ll bit[mxN];
void update (int x, int val) {
    for (; x < mxN; x += x & (-x))
        bit[x] += val;
}

ll query (int x) {
    ll ret = 0;
    for (; x > 0; x -= x & (-x))
        ret += bit[x];
    return ret;
}

vi gp[mxN];
int vis[mxN];

int c = 0;
void dfs (int a) {
    vis[a] = 1;
    c ++;
    for (int i: gp[a]) {
        if (!vis[i]) {
            dfs(i);
        }
    }
}

int Lis[mxN];
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    vector<ll> ans = {0, 0, n, n};

    int mx = 0;
    for (int i = 0; i < n; i ++) {
        cin >> num[i];
        ans[0] += query(mxN - 1) - query(num[i]); // 數前面有多少人比自己大
        update(num[i], 1);
        if (i + 1 != num[i]) {
            gp[i + 1].pb(num[i]);
            gp[num[i]].pb(i + 1);
        }
        int pos = lower_bound(Lis, Lis + mx + 1, num[i]) - Lis; // LIS Length
        mx = max(mx, pos);
        Lis[pos] = num[i];
    }

    ans[2] -= mx;
    for (int i = 1; i <= n; i ++) {
        if (!vis[i]) {
            c = 0;
            dfs(i);
            ans[1] += c - 1; // Tree Size - 1
        }
    }

    for (int i = n - 1; i >= 0; i --) {
        if (num[i] == ans[3]) ans[3] --;
    }
    cout << ans << "\n";
    return 0;
}