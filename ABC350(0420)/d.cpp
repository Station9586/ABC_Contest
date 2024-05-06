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

const int mxN = 2e5 + 10;

int p[mxN];
ll SIZE[mxN];

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

int n, m;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    FOR (i, 0, n) p[i] = i, SIZE[i] = 1;
    int a, b;
    REP (i, 0, m) {
        cin >> a >> b;
        Union(a, b);
    }

    ll ans = 0;
    FOR (i, 1, n) if (Find(i) == i) {
        ll x = SIZE[i];
        ans += x * (x - 1) / 2;
    }

    cout << ans - m << "\n";
    return 0;
}