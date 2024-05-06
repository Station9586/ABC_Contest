#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())

typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;

template<class T, class U> std::istream& operator >> (std::istream& in, std::pair<T, U>& p) { in >> p.first >> p.second; return in; }
template<class T, size_t N> std::istream& operator >> (std::istream& in, std::array<T, N>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::istream& operator >> (std::istream& in, std::vector<T>& a) { for (T &x: a) in >> x; return in; }
template<class T> std::ostream& operator << (std::ostream& out, std::vector<T>& a) { for (T x: a) out << x << " "; return out; }

using namespace std;

vi num = {17, 42, 35, 29, 12, 21, 6, 29, 22};
// vi num = {4, 8, 9, 15, 21, 21, 24, 25, 26, 28, 29, 34};

const int n = sz(num);

double average (const vi v) {
    double ret = 0;
    int n = sz(v);
    for (int i: v) ret += i;
    ret *= 1.0;
    ret /= n;
    return ret;
}

double median (const vi v) {
    double ret = 0;
    int n = sz(v);
    if (n & 1) ret = v[n >> 1];
    else ret = (v[n >> 1] + v[(n >> 1) - 1]) / 2.0;
    return ret;
}

int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(2);
    sort(all(num));
    cout << "num: " << num << "\n";
    int mn = num[0], mx = num.back();
    double Width = (mx - mn) / 3;
    cout << "Width: " << Width << '\n';
    cout << "\n";

    vi b1, b2, b3;
    for (int i: num) {
        if (i < mn + Width) b1.pb(i);
        else if (i < mn + Width * 2) b2.pb(i);
        else b3.pb(i);
    }
    
    cout << "Equal Width: \n";
    cout << "1. " << b1 << "\n";
    cout << "2. " << b2 << "\n";
    cout << "3. " << b3 << "\n";
    cout << "\n";
    vector<double> m1, m2, m3;
    double means1 = average(b1);
    double means2 = average(b2);
    double means3 = average(b3);

    for (int _: b1) m1.pb(means1);
    for (int _: b2) m2.pb(means2);
    for (int _: b3) m3.pb(means3);

    cout << "Means: \n";
    cout << "1. " << m1 << "\n";
    cout << "2. " << m2 << "\n";
    cout << "3. " << m3 << "\n";
    cout << "\n";
    double median1 = median(b1);
    double median2 = median(b2);
    double median3 = median(b3);

    vector<double> med1, med2, med3;
    for (int _: b1) med1.pb(median1);
    for (int _: b2) med2.pb(median2);
    for (int _: b3) med3.pb(median3);

    cout << "Median: \n";
    cout << "1. " << med1 << "\n";
    cout << "2. " << med2 << "\n";
    cout << "3. " << med3 << "\n";
    cout << "\n";
    vector<double> bound1, bound2, bound3;
    for (int i: b1) {
        if (abs(i - b1[0]) < abs(i - b1.back())) bound1.pb(b1[0]);
        else bound1.pb(b1.back());
    }
    for (int i: b2) {
        if (abs(i - b2[0]) < abs(i - b2.back())) bound2.pb(b2[0]);
        else bound2.pb(b2.back());
    }
    for (int i: b3) {
        if (abs(i - b3[0]) < abs(i - b3.back())) bound3.pb(b3[0]);
        else bound3.pb(b3.back());
    }

    cout << "Boundries: \n";
    cout << "1. " << bound1 << "\n";
    cout << "2. " << bound2 << "\n";
    cout << "3. " << bound3 << "\n";

    return 0;
}
