#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int max_n = 1000;
    int n;
    int grid[max_n + 1][max_n + 1];

    void solve()
    {
        scanf("%d", &n);

        grid[1][1] = 1;

        queue<pair<int, int>> q;

        q.push({1, 1});

        while (!q.empty())
        {
            auto cur = q.front();
            q.pop();

            list<pair<int, int>> moves = {
                { cur.first - 2, cur.second - 1 },
                { cur.first - 2, cur.second + 1 },
                { cur.first + 2, cur.second - 1 },
                { cur.first + 2, cur.second + 1 },
                { cur.first - 1, cur.second - 2 },
                { cur.first - 1, cur.second + 2 },
                { cur.first + 1, cur.second - 2 },
                { cur.first + 1, cur.second + 2 },
            };

            for (auto move : moves) {
                if (
                    move.first < 1 || move.second < 1 ||
                    move.first > n || move.second > n
                ) {
                    continue;
                }

                if (grid[move.first][move.second]) {
                    continue;
                }


                grid[move.first][move.second] = grid[cur.first][cur.second] + 1;
                q.push(move);
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                printf("%d ", grid[i][j] - 1);
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
        solve1::solve();
    }

    return 0;
}