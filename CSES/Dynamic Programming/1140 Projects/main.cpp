#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 2 * 1e5;
long long dp[maxN + 1];
array<int, 3> inputData[maxN + 1];

void solve()
{
    int n = 0;
    scanf("%d", &n);

    dp[0] = 0;
    inputData[0] = {0, 0, 0};
    
    for (int i = 1; i <= n; i++)
    {
        int start = 0, finish = 0, price = 0;
        scanf("%d%d%d", &start, &finish, &price);
        inputData[i] = {finish, start, price};
    }

    sort(inputData + 1, inputData + n + 1);

    for (int i = 1; i <= n; i++)
    {
        int prevProjId = upper_bound(
            inputData + 0, inputData + n + 1, array<int, 3>{inputData[i][1], 0, 0}
        ) - inputData - 1;

        dp[i] = max(dp[i - 1], dp[prevProjId] + inputData[i][2]);
    }

    printf("%lld", dp[n]);
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