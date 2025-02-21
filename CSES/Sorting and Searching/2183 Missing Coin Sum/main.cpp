#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
int coins[maxN];
 
void solve() {
    int n = 0;
    scanf("%d", &n);
 
    for (int i = 0; i < n; i++)
    {
        int v = 0;
        scanf("%d", &v);

        coins[i] = v;
    }

    sort(coins, coins + n);

    long long max = 0;

    for (int i = 0; i < n; i++)
    {
        if (coins[i] - max > 1)
        {
            break;
        }

        max += coins[i];
    }
    
 
    printf("%lld", max + 1);
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