#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1 // Bellman–Ford algorithm
{
    const int maxN = 2500;
    const int maxM = 5000;
    vector<int> neighbors[maxN + 1];
    array<int, 3> edges[maxM + 1];
    long long distance[maxN + 1];

    int from[maxN + 1];
    int from2[maxN + 1];

    deque<int> res;

    int N, M;

    // bool dfsFindCycle(int node)
    // {
    //     for (auto& neighbor : neighbors[node])
    //     {
    //         if (from[neighbor] == 0)
    //         {
    //             from[neighbor] = node;
    //             if (dfsFindCycle(neighbor))
    //             {
    //                 return true;
    //             }
    //         } else if (from[neighbor] == node) {
    //             res.push_front(node);
                
    //             long long cycleSum = (*upper_bound(edges + 1, edges + M + 1, array<int, 3>{ from[node], node, (int)-2e9 }))[2];

    //             int parent = from[node];

    //             while(parent != node)
    //             {
    //                 cycleSum =+ (*upper_bound(edges + 1, edges + M + 1, array<int, 3>{ from[parent], parent, (int)-2e9 }))[2];

    //                 res.push_front(parent);
    //                 parent = from[parent];
    //             }

    //             cycleSum =+ (*upper_bound(edges + 1, edges + M + 1, array<int, 3>{ from[parent], parent, (int)-2e9 }))[2];

    //             res.push_front(node);

    //             if (cycleSum < 0)
    //             {
    //                 return true;
    //             }

    //             res.clear();
    //         }
    //     }

    //     return false;
    // }

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            edges[i] = {a, b, c};
            neighbors[a].emplace_back(b);
        }

        sort(edges + 1, edges + M + 1);

        memset(distance, 0x3f, sizeof(distance));
        distance[1] = 0;

        bool improvement = true;
        for (int i = 1; i <= N && improvement; i++)
        {
            improvement = false;
            for (int edgeIdx = 1; edgeIdx <= M; edgeIdx++)
            {
                auto [a, b, w] = edges[edgeIdx];

                if (distance[a] + w < distance[b])
                {
                    improvement = true;
                    distance[b] = distance[a] + w;

                    from[b] = a;

                    if (i == N)
                    {
                        int parent = a;
                        
                        while (from2[parent] == 0)
                        {
                            from2[parent] = from[parent];
                            parent = from[parent];
                        }

                        int cur = from2[parent];
                        parent = from2[cur];

                        res.push_front(cur);
                        
                        while(parent != cur)
                        {
                            res.push_front(parent);
                            parent = from2[parent];
                        }

                        res.push_front(parent);

                        printf("YES\n");

                        for (int node : res)
                        {
                            printf("%d ", node);
                        }

                        return;
                    }
                }
            }
        }

        printf("NO\n");
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