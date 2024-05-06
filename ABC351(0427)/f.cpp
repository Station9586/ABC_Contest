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
using pil = pair<int, ll>;

const int mxN = 4e5 + 10;
int n;
int num[mxN];

struct Node {
    ll val;
    int cnt;
    Node *lch, *rch;
    Node () {
        val = 0;
        cnt = 0;
        lch = rch = nullptr;
    }
    void pull () { 
        val = lch->val + rch->val; 
        cnt = lch->cnt + rch->cnt;
    }
};

void update (Node *st, int L, int R, int pos, ll x) {
    if (st->lch == nullptr) st->lch = new Node();
    if (st->rch == nullptr) st->rch = new Node();
    if (L == R) {
        st->val += x;
        st->cnt ++;
        return;
    }
    int mid = (L + R) >> 1;
    if (pos <= mid) update(st->lch, L, mid, pos, x);
    else update(st->rch, mid + 1, R, pos, x);
    st->pull();
}

pil operator + (const pil &a, const pil &b) {
    pil ret;
    ret.first = a.first + b.first;
    ret.second = a.second + b.second;
    return ret;
}

pil query (Node *st, int L, int R, int l, int r) {
    if (l > R or r < L) return {0, 0};
    if (st == nullptr) return {0, 0};
    if (l <= L and R <= r) return {st->cnt, st->val};
    int mid = (L + R) >> 1;
    return query(st->lch, L, mid, l, r) + query(st->rch, mid + 1, R, l, r);
}


int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    Node *st = new Node();
    FOR (i, 1, n) cin >> num[i];
    ll ans = 0;
    IFOR (i, 1, n + 1) {
        auto [cnt, sum] = query(st, 1, 1e8, num[i], 1e8);
        ans += sum;
        ans -= 1ll * cnt * num[i];
        update(st, 1, 1e8, num[i], num[i]);
    }
    cout << ans << "\n";
    return 0;
}

// #include <bits/stdc++.h>
// #define pb push_back
// #define all(x) (x).begin(), (x).end()
// #define sz(v) ((int) (v).size())
// #define FOR(i, a, b) for (int i = a; i <= b; i ++)
// #define REP(i, a, b) for (int i = a; i < b; i ++)
// #define IFOR(i, a, b) for (int i = b - 1; i >= a; i --) 

// typedef long long ll;
// typedef std::vector<int> vi;
// typedef std::pair<int, int> pi;

// template<class T> bool chmin (T &a, const T &b) { return a > b? (a = b, true): false; }
// template<class T> bool chmax (T &a, const T &b) { return a < b? (a = b, true): false; }
// template<class T> std::vector<T> sort_unique (std::vector<T> v) { std::sort(all(v)), v.erase(std::unique(all(v)), v.end()); return v; }

// using namespace std;

// using pil = pair<int, ll>;
// const int mxN = 4e5 + 10;
// int n;
// int num[mxN];

// pil operator + (const pil &a, const pil &b) {
//     pil ret;
//     ret.first = a.first + b.first;
//     ret.second = a.second + b.second;
//     return ret;
// }

// ll st[mxN << 1];
// int st2[mxN << 1];

// void update (int p, ll x) {
//     p += n;
//     st[p] += x;
//     st2[p] ++;
//     p >>= 1;
//     while (p > 1) {
//         st[p] = st[p << 1] + st[p << 1 | 1];
//         st2[p] = st2[p << 1] + st2[p << 1 | 1];
//         p >>= 1;
//     }
// }

// pil query (int a, int b) {
//     a += n, b += n;
//     pil ret = {0, 0};
//     for (; a <= b; a >>= 1, b >>= 1) {
//         if (a & 1) {
//             ret = ret + make_pair(st2[a], st[a]);
//             a ++;
//         }
//         if (~b & 1) {
//             ret = ret + make_pair(st2[b], st[b]); 
//             b --;
//         }

//     }
//     return ret;
// }

// int main (int argc, const char *argv[]) {
//     cin.tie(NULL);
//     ios_base::sync_with_stdio(false);
//     cin >> n;
//     vi v;
//     FOR (i, 1, n) {
//         cin >> num[i];
//         v.pb(num[i]);
//     }
//     v = sort_unique(v);
//     auto id = [&] (int a) {
//         return lower_bound(all(v), a) - v.begin() + 1;
//     };
//     ll ans = 0;
//     int N = sz(v);
//     IFOR (i, 1, n + 1) {
//         auto [cnt, sum] = query(id(num[i]), N);
//         ans += sum;
//         ans -= 1ll * cnt * num[i];
//         update(id(num[i]), num[i]);
//     }
//     cout << ans << "\n";
//     return 0;
// }