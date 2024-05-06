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


ll n;
int a, x, y;
map<ll, double> mp;

double solve (ll n) {
    if (mp.count(n)) return mp[n];
    double ans = solve(n / a);
    double sum = 0;
    FOR (i, 2, 6)
        sum += solve(n / i);
    sum /= 6;
    sum += y;
    sum *= 6;
    sum /= 5;
    return mp[n] = min(ans + x, sum);
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> a >> x >> y;
    mp[0] = 0;
    cout << fixed << setprecision(10) << solve(n) << "\n";
    return 0;
}