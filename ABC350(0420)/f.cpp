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

const int mxN = 5e5 + 10;
string s;

mt19937 Random(time(NULL));

struct Node {
    ll key;
    ll pri, size;
    Node *lch, *rch;
    int rev_tag;
    int is_change;
    Node () {
        lch = rch = nullptr;
        size = 1;
        pri = Random();
        rev_tag = 0;
        key = 0;
        is_change = 0;
    }

    void pull () {
        size = 1;
        if (lch != nullptr) size += lch->size;
        if (rch != nullptr) size += rch->size;
    }

    void rev () {
        swap(lch, rch);
        rev_tag ^= 1;
        is_change ^= 1;
    }

    void push () {
        if (rev_tag) {
            if (lch != nullptr) lch->rev();
            if (rch != nullptr) rch->rev();
            rev_tag = 0;
        }
    }
};

Node *new_Node (ll k) {
    static Node ret[mxN * 2];
    static int ptr = 0;
    ret[ptr].key = k;
    return &ret[ptr ++];
}

Node *merge (Node *a, Node *b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    if (a->pri < b->pri) {
        a->push();
        a->rch = merge(a->rch, b);
        a->pull();
        return a;
    }else {
        b->push();
        b->lch = merge(a, b->lch);
        b->pull();
        return b;
    }
}

inline ll size (Node *p) { return (p == nullptr)? 0: p->size; }

void split_by_size (Node *p, Node *&a, Node *&b, int k) {
    if (p == nullptr) {
        a = b = nullptr;
        return;
    }
    p->push();
    if (size(p->lch) < k) {
        a = p;
        split_by_size(p->rch, a->rch, b, k - size(p->lch) - 1);
        a->pull();
    }else {
        b = p;
        split_by_size(p->lch, a, b->lch, k);
        b->pull();
    }
}

void reverse (Node *&p, int L, int R) {
    Node *a, *b, *c;
    split_by_size(p, b, c, R);
    split_by_size(b, a, b, L - 1);
    b->rev();
    p = merge(merge(a, b), c);
}

pi get_index (Node *&p, int i) {
    Node *a, *b, *c;
    split_by_size(p, a, c, i - 1);
    split_by_size(c, b, c, 1);
    int ret = b->key;
    int rv = b->is_change;
    p = merge(merge(a, b), c);
    return {ret, rv};
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> s;
    int n = sz(s);
    Node *tp = nullptr;
    FOR (i, 1, n) tp = merge(tp, new_Node(i));

    stack<int> stk;
    int a, b;
    REP (i, 0, n) {
        char c = s[i];
        if (c == '(') 
            stk.push(i);
        else if (c == ')') {
            a = stk.top();
            stk.pop();
            b = i;
            reverse(tp, a + 1, b + 1);
        }
    }

    string ans = "";
    FOR (i, 1, n) {
        auto [id, rev] = get_index(tp, i);
        char c = s[id - 1];
        if (c == '(' or c == ')') continue;
        if (rev) {
            if (c >= 'a' and c <= 'z') 
                ans += c - 'a' + 'A';
            else 
                ans += c - 'A' + 'a';
        }else ans += c;
    }
    cout << ans << "\n";
    return 0;
}