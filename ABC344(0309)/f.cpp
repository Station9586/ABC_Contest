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

vi num = {200, 300, 400, 600, 1000};
const int n = sz(num);
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(4);
    vi tmp = num;
    sort(all(tmp));
    int mn = tmp[0], mx = tmp.back();
    vector<double> nor, z;
    for (int i: num) 
        nor.pb((i - mn) * 1.0 / (mx - mn));

    cout << "Origin: ";
    cout << num << "\n\n";
    cout << "Min-Max Normalization: ";
    cout << nor << "\n\n";

    double mean = 0, sd = 0;
    for (int i: num) mean += i;
    mean /= n * 1.0;
    // cout << "mean: " << mean << "\n";
    for (int i: num) 
        sd += (i - mean) * (i - mean) * 1.0;

    sd /= n * 1.0;
    sd = sqrt(sd);
    // cout << "SD: " << sd << "\n";
    for (int i: num) z.pb((i - mean) * 1.0 / sd);
    cout << "Z-value Normalization: " << z << "\n";
    return 0;
}