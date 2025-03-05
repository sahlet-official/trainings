#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
int n;
 
void solve() {
    scanf("%d", &n);

    long long sum = 0;
    int maxT = INT_MIN;
 
    for (int i = 0; i < n; i++)
    {
        int t = 0;
        scanf("%d", &t);

        sum += t;
        maxT = max(maxT, t);
    }

    long long res = 2ll * maxT;

    if (res < sum)
    {
        res = sum;
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