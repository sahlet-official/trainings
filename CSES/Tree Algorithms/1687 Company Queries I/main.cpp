#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 2e5;
    const int maxJumps = ceil(log2(maxN)) - 1;
    int bosses[maxN + 1][maxJumps + 1];
    int N, Q;

    int processQuery(int employee, int steps)
    {
        int boss = employee;
        for (int jump = maxJumps; jump >= 0; jump--)
        {
            if (steps >= (1 << jump))
            {
                boss = bosses[boss][jump];
                steps -= (1 << jump);
                if (boss == -1)
                {
                    break;
                }
            }
        }
        
        return boss;
    }

    void init()
    {
        for (int jump = 1; jump <= maxJumps; jump++)
        {
            for (int i = 1; i <= N; i++)
            {
                if (bosses[i][jump - 1] == -1)
                {
                    bosses[i][jump] = -1;
                    continue;
                }

                bosses[i][jump] = bosses[bosses[i][jump - 1]][jump - 1];
            }
        }
    }

    void solve()
    {
        scanf("%d%d", &N, &Q);

        bosses[1][0] = -1;

        for (int i = 2; i <= N; i++)
        {
            int boss = 0;
            scanf("%d", &boss);

            bosses[i][0] = boss;
        }

        init();

        for (int i = 1; i <= Q; i++)
        {
            int employee = 0, steps = 0;
            scanf("%d%d", &employee, &steps);
            printf("%d\n", processQuery(employee, steps));
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