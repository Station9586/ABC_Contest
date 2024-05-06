#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

template<typename... T> void read (T&... args) { ((std::cin >> args), ...); }
template<typename... T> void put (T&&... args) { ((std::cout << args << " "), ...); }
template<typename... T> void print (T&&... args) { ((std::cout << args << " "), ...); std::cout << "\n"; }

template<class T> using max_heap = std::priority_queue<T>;
template<class T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template<class T> bool chmin (T &a, const T &b) { return a > b? (a = b, true): false; }
template<class T> bool chmax (T &a, const T &b) { return a < b? (a = b, true): false; }
template<class T> std::vector<T> sort_unique (std::vector<T> v) { std::sort(all(v)), v.erase(std::unique(all(v)), v.end()); return v; }

template<class T, class U> std::istream& operator >> (std::istream& in, std::pair<T, U>& p) { in >> p.first >> p.second; return in; }
template<class T, size_t N> std::istream& operator >> (std::istream& in, std::array<T, N>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::istream& operator >> (std::istream& in, std::vector<T>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::ostream& operator << (std::ostream& out, std::vector<T>& a) { for (T &x: a) out << x << " "; return out; }

template<class T> constexpr T fld (const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }
template<class T> constexpr T cld (const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }
template<typename T> inline T __lg (T __n) { T __k; for (__k = 0; __n != 0; __n >>= 1) ++ __k; return __k - 1; }

using namespace std;

// class Solution {
// public:
//     int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
//         int ret = 0;
//         int n = (int)status.size();
//         queue<int> q;
//         vector<int> ok = status;
//         vector<bool> found(n, false);

//         for (int i: initialBoxes) {
//             found[i] = true;
//             if (ok[i]) q.push(i);
//         }

//         while (!q.empty()) {
//             int now = q.front();
//             q.pop();
//             ret += candies[now];
//             for (int i: containedBoxes[now]) {
//                 found[i] = 1;
//                 if (ok[i]) q.push(i);
//             }
//             for (int i: keys[now]) {
//                 if (!ok[i] and found[i]) q.push(i);
//                 ok[i] = 1;
//             }
//         }
//         return ret;
//     }
// };
#ifdef LOCAL
#define debug(HEHE...) std::cout << "[" << #HEHE << "] : ", dout(HEHE)
void dout() { std::cout << '\n'; }
template<typename T, typename...U> 
void dout(T t, U...u) { std::cout << t << (sizeof...(u) ? ", " : ""), dout(u...); }
#else
#define debug(...) 7122
#endif

class Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        const int mxN = 1010;
        int n = (int)edges.size();
        int m = (int)passingFees.size();
        int dp[mxN][mxN];
        memset(dp, -1, sizeof(dp));
        vector<int> gp[mxN];
        for (int i = 0, a, b; i < n; i ++) {
            a = edges[i][0], b = edges[i][1];
            gp[a].push_back(i);
            gp[b].push_back(i);
        }

        dp[0][0] = passingFees[0];
        for (int i = 0; i <= maxTime; i ++) {
            for (int x = 0; x < m; x ++) {
                if (i > 0 and dp[i - 1][x] != -1 and (dp[i][x] == -1 or dp[i][x] > dp[i - 1][x]))
                    dp[i][x] = dp[i - 1][x];
                if (dp[i][x] != -1 and (i == 0 or dp[i][x] != dp[i - 1][x])) {
                    for (int v: gp[x]) {
                        int w = edges[v][0] + edges[v][1] - x;
                        int timer = i + edges[v][2];
                        int cost = dp[i][x] + passingFees[w];
                        debug(i, x, w, v, cost);
                        if (timer <= maxTime and (dp[timer][w] == -1 or dp[timer][w] > cost))
                            dp[timer][w] = cost;
                    }
                }
            }
        }
        int ret = -1;
        for (int i = 0; i <= maxTime; i ++) {
            if (dp[i][m - 1] != -1 and (ret == -1 or ret > dp[i][m - 1]))
                ret = dp[i][m - 1];
        }
        return ret;
    }
};

int main (int argc, const char* argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    // vi status = {1,0,1,0};
    // vi candies = {7,5,4,100};
    // vector<vi> keys = {{}, {}, {1}, {}};
    // vector<vi> containedBoxes = {{1, 2}, {3}, {}, {}};
    // vi initialBoxes = {0};
    int mx = 30;
    vector<vi> edges = {{0,1,10},{1,2,10},{2,5,10},{0,3,1},{3,4,10},{4,5,15}};
    vi passingFees = {5,1,2,20,20,3};

    Solution s;
    // cout << s.maxCandies(status, candies, keys, containedBoxes, initialBoxes) << "\n";
    cout << s.minCost(mx, edges, passingFees) << "\n";
    return 0;
}
