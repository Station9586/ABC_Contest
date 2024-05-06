#include <iostream>
#include <vector>
#include <set>
#include <utility>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

using namespace std;

const int mxN = 2e5 + 10;

int n, q;

ll ans[mxN];
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q;
    set<int> st;

    ll v = 0;
    int a;
    while (q --) {
        cin >> a;
        if (st.count(a)) {
            ans[a] += v;
            st.erase(a);
        }else {
            ans[a] -= v;
            st.insert(a);
        }
        v += sz(st);
    }

    while (!st.empty()) {
        int x = *st.begin();
        st.erase(st.begin());
        ans[x] += v;
    }

    for (int i = 1; i <= n; i ++) cout << ans[i] << " \n"[i == n];
    return 0;
}
