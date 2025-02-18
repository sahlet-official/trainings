#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

inline long long modMult(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

inline long long modPow(long long a, long long b)
{
    long long res = 1;
    while(b)
    {
        if (b % 2)
        {
            res = modMult(res, a);
        }

        b /= 2;
        a = modMult(a, a);
    }

    return res;
}

inline long long modInverse(long long a)
{
    return modPow(a, MOD - 2);
}

inline long long modDivide(long long a, long long b)
{
    a %= MOD;
    b %= MOD;
    if (a % b == 0) {
        return a / b;
    }

    return modMult(a, modInverse(b));
}

const int maxN = 500;
int dp[maxN*(maxN + 1) / 4 + 1];

void solve()
{
    int n = 0;
    scanf("%d", &n);

    dp[0] = 1;
    int limit1 = n*(n + 1) / 2;

    if (limit1 % 2)
    {
        printf("%d", 0);
        return;
    }

    limit1 /= 2;

    for (int i = 2 /*1*/; i <= n; i++)
    {
        int limit2 = i*(i + 1) / 2;
        int limit = min(limit1, limit2);
        for (int s = limit; s >= i; s--)
        {
            dp[s] = modSum(dp[s], dp[s - i]);
        }
    }

    //printf("%d", modDivide(dp[limit1], 2));
    printf("%d", dp[limit1]);
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
        solve();
    }

    return 0;
}