#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

using namespace std;

const int mxN = 2e5 + 10;

int n, q;
int num[mxN];

struct Node {
    int mx, mxcnt, mx2, mx2cnt;
    Node *lch, *rch;

    Node () {
        mx = mxcnt = mx2 = mx2cnt = 0;
        lch = rch = nullptr;
    }

    void apply (int m1, int m2, int c1, int c2) {
        if (m1 > m2) {
            mx2 = m1;
            mx2cnt = c1;
        }else if (m1 < m2) {
            mx2 = m2;
            mx2cnt = c2;
        }else {
            mx2 = m1;
            mx2cnt = c1 + c2;
        }
    }

    void pull () {
        mx = max(lch->mx, rch->mx);
        if (lch->mx > rch->mx) {
            mxcnt = lch->mxcnt;
            apply(lch->mx2, rch->mx, lch->mx2cnt, rch->mxcnt);
        }else if (lch->mx < rch->mx) {
            mxcnt = rch->mxcnt;
            apply(lch->mx, rch->mx2, lch->mxcnt, rch->mx2cnt);
        }else {
            mxcnt = lch->mxcnt + rch->mxcnt;
            apply(lch->mx2, rch->mx2, lch->mx2cnt, rch->mx2cnt);
        }
    }

    friend Node operator + (const Node &a, const Node &b) {
        Node ret;
        ret.mx = max(a.mx, b.mx);
        if (a.mx > b.mx) {
            ret.mxcnt = a.mxcnt;
            ret.apply(a.mx2, b.mx, a.mx2cnt, b.mxcnt);
        }else if (a.mx < b.mx) {
            ret.mxcnt = b.mxcnt;
            ret.apply(a.mx, b.mx2, a.mxcnt, b.mx2cnt);
        }else {
            ret.mxcnt = a.mxcnt + b.mxcnt;
            ret.apply(a.mx2, b.mx2, a.mx2cnt, b.mx2cnt);
        }
        return ret;
    }
};

Node *build (int L, int R) {
    Node *st = new Node();
    if (L == R) {
        st->mx = num[L];
        st->mxcnt = 1;
        return st;
    }
    int mid = (L + R) >> 1;
    st->lch = build(L, mid);
    st->rch = build(mid + 1, R);
    st->pull();
    return st;
}

void update (Node *st, int L, int R, int pos, int x) {
    if (L == R) {
        st->mx = x;
        return;
    }
    int mid = (L + R) >> 1;
    if (pos <= mid) update(st->lch, L, mid, pos, x);
    else update(st->rch, mid + 1, R, pos, x);
    st->pull();
}

Node query (Node *st, int L, int R, int l, int r) {
    if (l > R or r < L) return {};
    if (l <= L and R <= r) return *st;
    int mid = (L + R) >> 1;
    return query(st->lch, L, mid, l, r) + query(st->rch, mid + 1, R, l, r);
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) cin >> num[i];
    Node *st = build(1, n);
    int op, a, b;
    while (q --) {
        cin >> op >> a >> b;
        if (op == 1) update(st, 1, n, a, b);
        else if (op == 2) {
            Node q = query(st, 1, n, a, b);
            cout << q.mx2cnt << "\n";
        }
    }
    return 0;
}