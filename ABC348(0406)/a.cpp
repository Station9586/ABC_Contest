#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

using namespace std;


int n;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        if (i % 3 == 0) cout << "x";
        else cout << "o";
    }
    cout << "\n";
    return 0;
}