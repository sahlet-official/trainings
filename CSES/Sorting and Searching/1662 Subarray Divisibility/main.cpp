#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
unordered_map<long long, int> m;
 
void solve() {
    int n = 0;
    scanf("%d", &n);

    m.reserve(4 * maxN);

    long long res = 0;
    int rest = 0;
    m[0] = 1;
 
    for (int i = 0; i < n; i++)
    {
        int val = 0;
        scanf("%d", &val);

        rest = ((rest + val) % n + n) % n;

        res += m[rest];
        
        m[rest] += 1;
    }

    printf("%lld", res);
}
 
 
int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
 
    long long testsNumber = 1;
 
    //cin >> testsNumber;
 
    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }
 
    return 0;
}