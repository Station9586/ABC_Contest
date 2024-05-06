#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

int n, q;
string s;

struct Node {
    int mx[2];
    int l[2], r[2];
    int len;
    Node *lch, *rch;
    int tag = 0;
    Node () {
        for (int i = 0; i < 2; i ++) mx[i] = l[i] = r[i] = 0;
        len = 0;
        lch = rch = nullptr;
        tag = 0;
    }

    Node (char c) {
        for (int i = 0; i < 2; i ++) mx[i] = l[i] = r[i] = (c == '0' + i);
        len = 1;
    }
    
    void rev () {
        swap(mx[0], mx[1]);
        swap(l[0], l[1]);
        swap(r[0], r[1]);
    }

    friend Node operator + (const Node &l, const Node &r) {
        Node ret;
        for (int i = 0; i < 2; i ++) {
            ret.l[i] = l.l[i] + (l.l[i] == l.len? r.l[i]: 0);
            ret.r[i] = r.r[i] + (r.r[i] == r.len? l.r[i]: 0);
            ret.mx[i] = max({l.mx[i], r.mx[i], l.r[i] + r.l[i]});
        }
        ret.len = l.len + r.len;
        return ret;
    }

    void pull () {
        for (int i = 0; i < 2; i ++) {
            l[i] = lch->l[i] + ((lch->l[i] == lch->len)? rch->l[i]: 0);
            r[i] = rch->r[i] + ((rch->r[i] == rch->len)? lch->r[i]: 0);
            mx[i] = max({lch->mx[i], rch->mx[i], lch->r[i] + rch->l[i]});
        }
        len = lch->len + rch->len;
    }
};

Node *build (int L, int R) {
    Node *st = new Node();
    if (L == R) {
        *st = Node(s[L - 1]);
        return st;
    }
    int mid = (L + R) >> 1;
    st->lch = build(L, mid);
    st->rch = build(mid + 1, R);
    st->pull();
    return st;
}

void apply (Node *st) {
    st->rev();
    st->tag ^= 1;
}

void push (Node *st) {
    if (st->tag) {
        apply(st->lch);
        apply(st->rch);
        st->tag = 0;
    }
}

void update (Node *st, int L, int R, int l, int r) {
    if (l > R or r < L) return;
    if (l <= L and R <= r) {
        apply(st);
        return;
    }
    push(st);
    int mid = (L + R) >> 1;
    update(st->lch, L, mid, l, r);
    update(st->rch, mid + 1, R, l, r);
    st->pull();
}

Node query (Node *st, int L, int R, int l, int r) {
    if (l > R or r < L) return {};
    if (l <= L and R <= r) return *st;
    push(st);
    int mid = (L + R) >> 1;
    return query(st->lch, L, mid, l, r) + query(st->rch, mid + 1, R, l, r);
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> q >> s;
    Node *st = build(1, n);
    int c, L, R;
    while (q --) {
        cin >> c >> L >> R;
        if (c == 1) update(st, 1, n, L, R);
        else if (c == 2) cout << query(st, 1, n, L, R).mx[1] << "\n";
    }
    return 0;
}
