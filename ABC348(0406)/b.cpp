#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;


template<class T> bool chmin (T &a, const T &b) { return a > b? (a = b, true): false; }
template<class T> bool chmax (T &a, const T &b) { return a < b? (a = b, true): false; }
template<class T> std::vector<T> sort_unique (std::vector<T> v) { std::sort(all(v)), v.erase(std::unique(all(v)), v.end()); return v; }

using namespace std;

const int mxN = 1010;
using tp = array<int, 3>;

int n;

vector<tp> v;

inline double dis (int a, int b, int a2, int b2) {
    return sqrt(pow(a - a2, 2) + pow(b - b2, 2));
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    int a, b;
    for (int i = 1; i <= n; i ++) {
        cin >> a >> b;
        v.pb({a, b, i});
    }

    vi ans;
    for (int i = 0; i < n; i ++) {
        int mn = mxN;
        double mx = 0;
        for (int j = 0; j < n; j ++) {
            if (j == i) continue;
            double d = dis(v[i][0], v[i][1], v[j][0], v[j][1]);
            if (chmax(mx, d)) mn = v[j][2];
            else if (mx == d) mn = min(mn, v[j][2]);
        }
        ans.pb(mn);
    }

    for (int i: ans) cout << i << "\n";
    return 0;
}