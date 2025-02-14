#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

const int maxN = 1e6;
pair<int, int> dp[maxN + 1]; // first - when last are separated, second - when last are together

void fillDP()
{
    dp[1].first = 1;
    dp[1].second = 1;

    for (int i = 2; i <= maxN; i++)
    {
        dp[i].first = modSum(dp[i-1].second, 4ll * dp[i-1].first);
        dp[i].second = modSum(2ll * dp[i-1].second, dp[i-1].first);
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;
    scanf("%lld", &testsNumber);

    fillDP();

    for (int i = 0; i < testsNumber; i++)
    {
        int n = 0;
        scanf("%d", &n);
        printf("%d\n", modSum(dp[n].first, dp[n].second));
    }

    return 0;
}