#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1 // Floyd–Warshall algorithm
{
    const int maxN = 500;
    const int maxM = maxN*maxN;
    long long INF = 0x3f3f3f3f3f3f3f3f;
    long long distance[maxN + 1][maxN + 1];
    int N, M, Q;

    void solve()
    {
        scanf("%d%d%d", &N, &M, &Q);

        memset(distance, INF, sizeof(distance));

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            if (a > b) swap(a, b);
            distance[a][b] = min(distance[a][b], (long long)c);
        }

        for (int k = 1; k <= N; k++)
        {
            distance[k][k] = 0;
            for (int i = 1; i <= N; i++)
            {
                for (int j = i + 1; j <= N; j++)
                {
                    distance[i][j] = min(distance[i][j], distance[min(i, k)][max(i, k)] + distance[min(j, k)][max(j, k)]);
                }
            }
        }
        
        for (int i = 1; i <= Q; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            if (a > b) swap(a, b);

            printf("%lld\n", distance[a][b] == INF ? -1 : distance[a][b]);
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