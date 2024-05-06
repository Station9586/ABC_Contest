// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

using namespace std;

const int mxN = 2e5 + 10;

int n, m, q;

int p[mxN];
int Find (int a) {
    if (p[a] < 0) return a;
    return p[a] = Find(p[a]);
}

void Union (int a, int b) {
    a = Find(a), b = Find(b);
    if (a == b) return;
    if (p[a] < p[b]) swap(a, b);
    p[b] += p[a];
    p[a] = b;
}

vector<pi> qry;
set<pi> st;

vi ans(mxN, 0);
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    memset(p, -1, sizeof(p));
    cin >> n >> m >> q;
    int a, b;
    for (int i = 0; i < m; i ++) {
        cin >> a >> b;
        if (a > b) swap(a, b);
        st.insert({a, b});
    }

    for (int i = 0; i < q; i ++) {
        cin >> a >> b;
        if (a > b) swap(a, b);
        st.erase({a, b});
        qry.pb({a, b});
    }

    int friends = n;
    for (auto [a, b]: st) {
        if (Find(a) != Find(b)) {
            friends --;
            Union(a, b);
        }
    }

    for (int i = q - 1; i >= 0; i --) {
        ans[i] = friends;
        auto [a, b] = qry[i];
        if (Find(a) != Find(b)) {
            friends --;
            Union(a, b);
        }
    }

    for (int i = 0; i < q; i ++)
        cout << ans[i] << " \n"[i == q - 1];
    return 0;
}
