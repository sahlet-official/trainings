#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 100;
const int maxSum = maxN * 1000;
int dp[maxSum + 1];
int coins[maxN];

void solve()
{
    int n = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);
    }

    dp[0] = true;

    int maxCurSum = 0;
    int counter = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = maxCurSum; j >= 0; j--)
        {
            if (!dp[j + coins[i]] && dp[j])
            {
                dp[j + coins[i]] = true;
                counter++;
            }
        }

        maxCurSum += coins[i];
    }

    printf("%d\n", counter);

    for (int j = 1; j <= maxCurSum; j++)
    {
        if (dp[j])
        {
            printf("%d ", j);
        }
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    // cin >> testsNumber;
    // scanf("%lld", &testsNumber);

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}