#include <iostream>
#include <string.h>
#include <stdlib.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(v) ((int) (v).size())
#define FOR(i, a, b) for (int i = a; i <= b; i ++)
#define REP(i, a, b) for (int i = a; i < b; i ++)
#define IFOR(i, a, b) for (int i = b - 1; i >= a; i --) 

using namespace std;


string s;
int main (int argc, const char *argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> s;
    string tmp = "";
    for (int i = 3; i <= 5; i ++) {
        tmp += s[i];
    }
    int num = stoi(tmp);
    if (num == 316 or num > 349 or num < 1) cout << "No\n";
    else cout << "Yes\n";
    return 0;
}