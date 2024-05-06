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


template<class T> bool chmin (T &a, const T &b) { return a > b? (a = b, true): false; }
template<class T> bool chmax (T &a, const T &b) { return a < b? (a = b, true): false; }
template<class T> std::vector<T> sort_unique (std::vector<T> v) { std::sort(all(v)), v.erase(std::unique(all(v)), v.end()); return v; }

using namespace std;

const int mxN = 210;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

vector<string> s(mxN);

int n, m, k;
int energy[mxN][mxN];

int w[mxN][mxN], in[mxN][mxN];

bool go (int x, int y) {
    if (x >= 1 and x <= n and y >= 1 and y <= m and s[x][y] != '#') 
        return true;
    return false;
}

int sx, sy, ex, ey;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    FOR (i, 1, n) {
        cin >> s[i];
        s[i] = " " + s[i];
        FOR (j, 1, m) {
            w[i][j] = -1;
            if (s[i][j] == 'S') sx = i, sy = j;
            if (s[i][j] == 'T') ex = i, ey = j;
        }
    }
    cin >> k;
    int r, c, e;
    REP (i, 0, k) {
        cin >> r >> c >> e;
        energy[r][c] = e;
    }

    queue<pi> q;
    q.push({sx, sy});
    w[sx][sy] = energy[sx][sy];

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        in[x][y] = 0;
        if (w[x][y] == 0) continue;
        REP (i, 0, 4) {
            int nx = x + dx[i], ny = y + dy[i];
            if (go(nx, ny)) {
                int d = w[x][y] - 1;
                d = max(d, energy[nx][ny]);
                if (chmax(w[nx][ny], d) and !in[nx][ny]) {
                    q.push({nx, ny});
                    in[nx][ny] = 1;
                }
            }
        }
    }

    if (w[ex][ey] >= 0) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}