#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

using namespace std;

const int mxN = 110;

int dp[mxN][mxN];
string s;

int n, m;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    cin >> s;
    int len = sz(s);
    cin >> n;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < mxN; j ++)
            dp[i + 1][j] = dp[i][j];
        cin >> m;
        while (m --) {
            string s2;
            cin >> s2;
            int s2len = sz(s2);
            for (int j = 0; j + s2len <= len; j ++) {
                bool ok = 1;
                for (int k = 0; k < s2len; k ++) {
                    if (s[j + k] != s2[k]) {
                        ok = 0;
                        break;
                    }
                }
                if (ok) 
                    dp[i + 1][j + s2len] = min(dp[i + 1][j + s2len], dp[i][j] + 1);
            }
        }
    }

    if (dp[n][len] > 5e8) cout << "-1\n";
    else cout << dp[n][len] << "\n";
    return 0;
}