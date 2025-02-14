#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxStrLen = 5000;
char str1[maxStrLen + 2];
char str2[maxStrLen + 2];
int dp[maxStrLen + 2][maxStrLen + 2];

void solve()
{
    scanf("%s", str1 + 1);
    scanf("%s", str2 + 1);

    int n = strlen(str1 + 1);
    int m = strlen(str2 + 1);

    for (size_t i = 1; i <= n; i++)
    {
        dp[i][0] = i;
    }

    for (size_t j = 1; j <= m; j++)
    {
        dp[0][j] = j;
    }

    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            dp[i][j] = min({
                dp[i - 1][j] + 1,
                dp[i][j - 1] + 1,
                dp[i - 1][j - 1] + (str1[i] == str2[j] ? 0 : 1)
            });
        }
    }
    
    printf("%d", dp[n][m]);
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