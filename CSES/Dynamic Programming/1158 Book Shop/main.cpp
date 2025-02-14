#include <iostream>
#include <bits/stdc++.h>

using namespace std;
 
void solve() {
    int n = 0, x = 0;
    scanf("%d%d", &n, &x);

    vector<int> prices(n);
    vector<int> pages(n);

    for (int i = 0; i < n; i++)
    {
        int v = 0;
        scanf("%d", &v);
        prices[i] = v;
    }

    for (int i = 0; i < n; i++)
    {
        int v = 0;
        scanf("%d", &v);
        pages[i] = v;
    }

    vector<int> dp(x + 1);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = x; j >= prices[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - prices[i]] + pages[i]);
        }
    }

    printf("%d", dp.back());
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