#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

int dp[1000][1000];

void solve() {
    int n = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        char s[n + 1];
        scanf("%s", &s);
        for (int j = 0; j < n; j++)
        {
            if (s[j] == '*')
            {
                dp[i][j] = -1;
            }
            else if (s[j] == '.')
            {
                dp[i][j] = 0;
            }
        }
    }

    if (dp[0][0] == -1 || dp[n-1][n-1] == -1)
    {
        printf("%d", 0);
        return;
    }

    dp[0][0] = 1;

    for (size_t i = 1; i < n; i++)
    {
        if (dp[0][i] == 0) dp[0][i] = dp[0][i - 1];
        if (dp[i][0] == 0) dp[i][0] = dp[i - 1][0];
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            int res1 = dp[i-1][j] == -1 ? 0 : dp[i-1][j];
            int res2 = dp[i][j-1] == -1 ? 0 : dp[i][j-1];

            dp[i][j] = dp[i][j] == -1 ? -1 : modSum(res1, res2);
        }
    }

    printf("%d", dp[n-1][n-1]);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    // ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}