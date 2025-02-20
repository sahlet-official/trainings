#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
 
void solve() {
    int n = 0;
    scanf("%d", &n);

    long long res = LLONG_MIN;
    long long cur = 0;
 
    for (int i = 0; i < n; i++)
    {
        long long v = 0;
        scanf("%lld", &v);

        cur = max(cur + v, v);
        res = max(res, cur);
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