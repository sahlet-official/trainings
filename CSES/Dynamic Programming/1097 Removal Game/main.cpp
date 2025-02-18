#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 5000;
int values[maxN + 1];
long long prefSum[maxN + 1];
long long dp[maxN + 1][maxN + 1];

long long solve(int i, int j)
{
    if (dp[i][j] != INT_MAX)
    {
        return dp[i][j];
    }

    if (i == j)
    {
        dp[i][j] = values[i];
    }
    else
    {
        dp[i][j] = max(
            values[i] + prefSum[j] - prefSum[i] - solve(i + 1, j),
            values[j] + prefSum[j - 1] - prefSum[i - 1] - solve(i, j - 1)
        );
    }

    return dp[i][j];
}

void solve1()
{
    fill(dp[0], dp[0] + sizeof(dp) / sizeof(dp[0][0]), INT_MAX);

    int n = 0;
    scanf("%d", &n);

    prefSum[0] = 0;

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &values[i + 1]);
        prefSum[i + 1] = values[i + 1] + prefSum[i];
    }

    printf("%lld", solve(1, n));
}

void solve2()
{
    //fill(dp[0], dp[0] + sizeof(dp) / sizeof(dp[0][0]), INT_MAX);

    int n = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &values[i + 1]);
    }

    for (int i = n; i >= 1; i--)
    {
        dp[i][i] = values[i];
        for (int j = i + 1; j <= n; j++)
        {
            dp[i][j] = max(
                values[i] - dp[i + 1][j],
                values[j] - dp[i][j - 1]
            );
        }
    }

    long long res = accumulate(begin(values), end(values), 0ll);

    printf("%lld", (res + dp[1][n]) / 2);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;
    //scanf("%lld", &testsNumber);

    for (int i = 0; i < testsNumber; i++)
    {
        //solve1();
        solve2();
    }

    return 0;
}