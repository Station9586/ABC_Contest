#include <iostream>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())
#define FOR(i, a, b) for (int i = a; i <= b; i ++)
#define REP(i, a, b) for (int i = a; i < b; i ++)
#define IFOR(i, a, b) for (int i = b - 1; i >= a; i --) 

using namespace std;


int n, q;
int num[1010];
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q;
    int sum = n;
    for (int i = 1; i <= n; i ++) num[i] = 1;
    for (int i = 1, a; i <= q; i ++) {
        cin >> a;
        if (num[a] == 1) {
            num[a] = 0;
            sum --;
        }else {
            num[a] = 1;
            sum ++;
        }
    }
    cout << sum << "\n";
    return 0;
}