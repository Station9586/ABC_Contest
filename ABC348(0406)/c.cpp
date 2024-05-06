#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

using namespace std;

int n;
map<int, int> mp;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    int a, b;
    for (int i = 0; i < n; i ++) {
        cin >> a >> b;
        if (mp[b] == 0) mp[b] = a;
        else mp[b] = min(mp[b], a);
    }

    int mx = 0;
    for (pair<int, int> i: mp) mx = max(mx, i.second);
    cout << mx << "\n";
    return 0;
}