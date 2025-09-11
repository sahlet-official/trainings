#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int max_n = 100;
    int n, a, b;
    int res1[max_n + 1], res2[max_n + 1];

    void solve()
    {
        scanf("%d%d%d", &n, &a, &b);

        if ((a + b) > n) {
            printf("NO\n");
            return;
        }

        if (!a && b || a && !b) {
            printf("NO\n");
            return;
        }

        printf("YES\n");

        for (int i = a + b + 1; i <= n; i++) {
            res1[i] = i;
            res2[i] = i;
        }

        int same = n - (a + b);
        int rest = a + b;

        for (int i = 1; i <= rest; i++) {
            res1[i] = i;
            res2[i] = (i + a) % rest;
        }

        res2[b] = rest;

        for (int i = 1; i <= n; i++) {
            printf("%d ", res1[i]);
        }
        printf("\n");

        for (int i = 1; i <= n; i++) {
            printf("%d ", res2[i]);
        }
        printf("\n");
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    // ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // std::cout.tie(0);

    long long testsNumber = 1;

    // cin >> testsNumber;
    scanf("%lld", &testsNumber);

    for (long long i = 0; i < testsNumber; i++)
    {
        solve1::solve();
    }

    return 0;
}