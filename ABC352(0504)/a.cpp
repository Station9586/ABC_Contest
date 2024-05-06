#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

using namespace std;

int n;
int x, y, z;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> x >> y >> z;
    if (x > y) swap(x, y);
    if (x <= z and z <= y) cout << "Yes\n";
    else cout << "No\n";    
    return 0;
}