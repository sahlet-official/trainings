#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int intMaxM = 100;
const int maxArrSize = 1e5;
int dp[intMaxM + 2][maxArrSize + 1];

const long long MOD = 1e9 + 7;

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

void solve() {
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);

    memset(dp, 0, sizeof(dp));

    {
        int v = 0;
        scanf("%d", &v);
        
        if (v == 0)
        {
            for (int i = 1; i <= m; i++)
            {
                dp[i][1] = 1;
            }
        }
        else
        {
            dp[v][1] = 1;
        }
    }

    for (int i = 2; i <= n; i++)
    {
        int v = 0;
        scanf("%d", &v);

        if (v == 0)
        {
            for (int j = 1; j <= m; j++)
            {
                dp[j][i] = modSum(modSum(dp[j][i-1], dp[j-1][i-1]), dp[j+1][i-1]);
            }
        }
        else
        {
            dp[v][i] = modSum(modSum(dp[v][i-1], dp[v-1][i-1]), dp[v+1][i-1]);;
        }
    }

    int res = 0;

    for (int j = 1; j <= m; j++)
    {
        res = modSum(res, dp[j][n]);
    }

    printf("%d", res);
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