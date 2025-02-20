#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 20;
const int maxSet = (1 << maxN) - 1;
pair<int, int> dp[maxSet + 1];
int w[maxN + 1];

void solve()
{
    int n = 0, x = 0;
    scanf("%d%d", &n, &x);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &w[i]);
    }

    int maxSet = (1 << n) - 1;

    dp[0] = {1, 0};

    for (int set = 1; set <= maxSet; set++)
    {
        dp[set] = {n + 1, 0};
        int collection = set;
        while (collection)
        {
            int person = -collection & collection;
            collection = collection & ~person;

            int personWeight = w[__builtin_ctz(person)];

            auto subres = dp[set & ~person];
            if (subres.second + personWeight > x)
            {
                subres.first += 1;
                subres.second = personWeight;
            }
            else
            {
                subres.second += personWeight;
            }

            dp[set] = min(dp[set], subres);
        }
    }

    printf("%d", dp[maxSet]);
}

void solve2()
{
    int n = 0, x = 0;
    scanf("%d%d", &n, &x);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &w[i]);
    }

    int maxSet = (1 << n) - 1;

    dp[0] = {1, 0};

    for (int set = 1; set <= maxSet; set++)
    {
        dp[set] = {n + 1, 0};
        for(int person = 0; person < n; person++)
        {
            if ((set & (1 << person)) == 0)
            {
                continue;
            }

            int personWeight = w[person];

            auto subres = dp[set & ~(1 << person)];
            if (subres.second + personWeight > x)
            {
                subres.first += 1;
                subres.second = personWeight;
            }
            else
            {
                subres.second += personWeight;
            }

            dp[set] = min(dp[set], subres);
        }
    }

    printf("%d", dp[maxSet]);
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