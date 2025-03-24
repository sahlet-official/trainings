#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 2e5;
    vector<int> neighbors[maxN + 1];
    int busy[maxN + 1];
    int diameterLength;
    int N;

    struct NodeInfo
    {
        int maxDist1 = 0;
        int maxDist2 = 0;
    };

    NodeInfo info[maxN + 1];

    int diameterPoint = 0;

    void dfsDiameter(int node = 1, int parent = 0)
    {
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent)
            {
                dfsDiameter(neighbor, node);

                int length = info[neighbor].maxDist1 + 1;

                if (length > info[node].maxDist1)
                {
                    swap(info[node].maxDist1, length);
                }

                if (length > info[node].maxDist2)
                {
                    swap(info[node].maxDist2, length);
                }
            }
        }

        int possibleDiameter = info[node].maxDist1 + info[node].maxDist2;
        if (possibleDiameter > diameterLength)
        {
            diameterLength = possibleDiameter;
            diameterPoint = node;
        }
    }

    int res[maxN + 1];

    void dfsMaxDist(int maxDist, int node = 1, int parent = 0)
    {
        res[node] = maxDist;

        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent)
            {
                dfsMaxDist(maxDist + 1, neighbor, node);
            }
        }
    }

    void solve()
    {
        scanf("%d", &N);

        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }

        dfsDiameter(1);

        bool diameterOdd = diameterLength % 2;
        int middlePoint = diameterPoint;
        //go to middle
        while (info[middlePoint].maxDist1 != (diameterLength + 1) / 2)
        {
            for (int neighbor : neighbors[middlePoint])
            {
                if (info[middlePoint].maxDist1 == (info[neighbor].maxDist1 + 1))
                {
                    middlePoint = neighbor;
                    break;
                }
            }
        }

        for (int neighbor : neighbors[middlePoint])
        {
            int maxDist = info[middlePoint].maxDist1 + 1;
            if (diameterOdd && info[middlePoint].maxDist1 == (info[neighbor].maxDist1 + 1))
            {
                maxDist--;
            }
            dfsMaxDist(maxDist, neighbor, middlePoint);
        }

        res[middlePoint] = info[middlePoint].maxDist1;

        for (int i = 1; i <= N; i++)
        {
            printf("%d ", res[i]);
        }
    }
}

namespace solve2
{
    const int maxN = 2e5;
    vector<int> neighbors[maxN + 1];
    int N;

    int info[maxN + 1][2];

    int theMostFarNode;

    void dfs(int node, int t, int parent = 0)
    {
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent)
            {
                info[neighbor][t] = info[node][t] + 1;

                if (info[neighbor][t] > info[theMostFarNode][t])
                {
                    theMostFarNode = neighbor;
                }

                dfs(neighbor, t, node);
            }
        }
    }

    int res[maxN + 1];

    void solve()
    {
        scanf("%d", &N);

        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }

        dfs(1, 0);

        memset(info, 0, sizeof info);

        dfs(theMostFarNode, 0); // theMostFarNode changed here
        dfs(theMostFarNode, 1);

        for (int i = 1; i <= N; i++)
        {
            printf("%d ", max(info[i][0], info[i][1]));
        }
    }
}

namespace solve3
{
    const int maxN = 2e5;
    vector<int> neighbors[maxN + 1];
    int N;

    struct NodeInfo
    {
        int maxDown1 = 0;
        int maxDown1Node = 0;
        int maxDown2 = 0;
        int maxUp = 0;
    };

    NodeInfo info[maxN + 1];

    void dfs1(int node = 1, int parent = 0)
    {
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent)
            {
                dfs1(neighbor, node);

                int length = info[neighbor].maxDown1 + 1;

                if (length > info[node].maxDown1)
                {
                    swap(info[node].maxDown1, length);
                    info[node].maxDown1Node = neighbor;
                }

                if (length > info[node].maxDown2)
                {
                    swap(info[node].maxDown2, length);
                }
            }
        }
    }

    void dfs2(int node = 1, int parent = 0)
    {
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent)
            {
                info[neighbor].maxUp = info[node].maxUp + 1;

                if (neighbor == info[node].maxDown1Node)
                {
                    info[neighbor].maxUp = max(info[neighbor].maxUp, info[node].maxDown2 + 1);
                }
                else
                {
                    info[neighbor].maxUp = max(info[neighbor].maxUp, info[node].maxDown1 + 1);
                }

                dfs2(neighbor, node);
            }
        }
    }

    void solve()
    {
        scanf("%d", &N);

        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }

        dfs1();
        dfs2();

        for (int i = 1; i <= N; i++)
        {
            printf("%d ", max(info[i].maxDown1, info[i].maxUp));
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
        //solve1::solve();
        //solve2::solve();
        solve3::solve();
    }

    return 0;
}