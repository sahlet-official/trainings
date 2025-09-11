#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int max_n = 100;
    const int max_depth = 128;
    int n;
    int grid[max_n + 1][max_n + 1];
    bool columns[max_n + 1][max_depth + 1], rows[max_n + 1][max_depth + 1];

    void solve()
    {
        scanf("%d", &n);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int min = -1;

                for (int k = 1; k <= max_depth; k++) {
                    if (!columns[j][k] && !rows[i][k]) {
                        min = k - 1;
                        columns[j][k] = rows[i][k] = true;
                        break;
                    }
                }

                grid[i][j] = min;
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                printf("%d ", grid[i][j]);
            }

            printf("\n");
        }
    }
}

namespace solve2
{
    const int max_n = 100;
    int n;
    int grid[max_n + 1][max_n + 1];

    void solve()
    {
        scanf("%d", &n);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                grid[i][j] = (i - 1) ^ (j - 1);
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                printf("%d ", grid[i][j]);
            }

            printf("\n");
        }
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
    // scanf("%lld", &testsNumber);

    for (long long i = 0; i < testsNumber; i++)
    {
        // solve1::solve();
        solve2::solve();
    }

    return 0;
}