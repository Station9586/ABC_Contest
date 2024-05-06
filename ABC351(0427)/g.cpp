#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())
#define FOR(i, a, b) for (int i = a; i <= b; i ++)
#define REP(i, b) for (int i = 0; i < b; i ++)
#define IFOR(i, a, b) for (int i = b - 1; i >= a; i --) 

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

template<class T, class U> std::istream& operator >> (std::istream& in, std::pair<T, U>& p) { in >> p.first >> p.second; return in; }
template<class T, size_t N> std::istream& operator >> (std::istream& in, std::array<T, N>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::istream& operator >> (std::istream& in, std::vector<T>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::ostream& operator << (std::ostream& out, std::vector<T>& a) { for (T x: a) out << x << " "; return out; }

template<typename... T> void read (T&... args) { ((std::cin >> args), ...); }
template<typename... T> void put (T&&... args) { ((std::cout << args << " "), ...); }
template<typename... T> void print (T&&... args) { ((std::cout << args << " "), ...); std::cout << "\n"; }

#ifdef LOCAL
#define debug(HEHE...) std::cout << "[" << #HEHE << "] : ", dout(HEHE)
void dout() { std::cout << '\n'; }
template<typename T, typename...U> 
void dout(T t, U...u) { std::cout << t << (sizeof...(u) ? ", " : ""), dout(u...); }
#else
#define debug(...) 7122
#endif

using namespace std;

const double weights[] = {0.7, 0.5, 0.3, 0.1};

double average (const vi &a) {
    int n = sz(a);
    int sum = accumulate(all(a), 0);
    return 1.0 * sum / n;
}

double dis (double a, double b) { return abs(a - b); }

double power_2 (double a) { return a * a; }

double Euclidean_distance (const vi &a, const vi &b) {
    int n = sz(a);
    double ret = 0;
    REP (i, n) ret += power_2(dis(a[i], b[i]));
    return sqrt(ret);
}

double Manhattan_distance (const vi &a, const vi &b) {
    int n = sz(a);
    double ret = 0.0;
    REP (i, n) ret += dis(a[i], b[i]);
    return ret;
}

double Weighted_distance (const vi &a, const vi &b) {
    int n = sz(a);
    double ret = 0.0;
    REP (i, n) ret += weights[i] * power_2(dis(a[i], b[i]));
    return sqrt(ret);
}

int main (int argc, const char *argv[]) {
    vi a = {1, 5, 7, 8, 12, 20}, b;
    vi split_a, split_b;
    double c1 = 1, c2 = 5;

    auto cluster = [&] (const vi &a) {
        for (int i: a) {
            if (dis(i, c1) < dis(i, c2)) split_a.emplace_back(i);
            else split_b.emplace_back(i);
        }
    };

    while (true) {
        split_a.clear(), split_b.clear();
        cluster(a), cluster(b);
        c1 = average(split_a), c2 = average(split_b);
        debug(split_a, split_b, c1, c2);
        if (a == split_a and b == split_b) break;
        a = split_a, b = split_b;
    }

    print("Set a:", a);
    print("Set b:", b);

    print("----------------------");

    vi PersonA = {18, 179, 58, 80};
    vi PersonB = {24, 180, 60, 60};
    // cout << fixed << setprecision(6);
    print("Euclidean_distance:", Euclidean_distance(PersonA, PersonB));
    print("Manhattan_distance:", Manhattan_distance(PersonA, PersonB));
    print("Weighted_distance:", Weighted_distance(PersonA, PersonB));
    return 0;
}