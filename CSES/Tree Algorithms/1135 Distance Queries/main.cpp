#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 2e5;
    const int maxJumps = ceil(log2(maxN)) - 1;
    vector<int> neighbors[maxN + 1];
    int ancestors[maxN + 1][maxJumps + 1];
    int depth[maxN + 1];
    int N, Q;

    int processQuery(int a, int b)
    {
        int res = 0;

        if (depth[a] < depth[b])
        {
            swap(a, b);
        }

        int steps = depth[a] - depth[b];

        res += steps;

        for (int jump = maxJumps; jump >= 0; jump--)
        {
            if (steps & (1 << jump))
            {
                a = ancestors[a][jump];
            }
        }

        if (a == b)
        {
            return res;
        }

        for (int jump = maxJumps; jump >= 0; jump--)
        {
            if (ancestors[a][jump] != ancestors[b][jump])
            {
                a = ancestors[a][jump];
                b = ancestors[b][jump];
                res += 2*(1 << jump);
            }
        }

        res += 2;
        
        return res;
    }

    void dfs(int node = 1, int parent = 0, int d = 0)
    {
        ancestors[node][0] = parent;
        depth[node] = d;

        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent) dfs(neighbor, node, d + 1);
        }
    }

    void init()
    {
        dfs();
        for (int jump = 1; jump <= maxJumps; jump++)
        {
            for (int i = 1; i <= N; i++)
            {
                ancestors[i][jump] = ancestors[ancestors[i][jump - 1]][jump - 1];
            }
        }
    }

    void solve()
    {
        scanf("%d%d", &N, &Q);

        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }

        init();

        for (int i = 1; i <= Q; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            printf("%d\n", processQuery(a, b));
        }
    }
}

namespace solve2
{
    const int maxN = 2e5;
    const int maxJumps = ceil(log2(maxN)) - 1;
    vector<int> neighbors[maxN + 1];
    int ancestors[maxN + 1][maxJumps + 1];
    int depth[maxN + 1];
    int N, Q;

    int lca(int employee1, int employee2)
    {
        if (depth[employee1] < depth[employee2])
        {
            swap(employee1, employee2);
        }

        int steps = depth[employee1] - depth[employee2];

        for (int jump = maxJumps; jump >= 0; jump--)
        {
            if (steps & (1 << jump))
            {
                employee1 = ancestors[employee1][jump];
            }
        }

        if (employee1 == employee2)
        {
            return employee1;
        }

        for (int jump = maxJumps; jump >= 0; jump--)
        {
            if (ancestors[employee1][jump] != ancestors[employee2][jump])
            {
                employee1 = ancestors[employee1][jump];
                employee2 = ancestors[employee2][jump];
            }
        }
        
        return ancestors[employee1][0];
    }

    int processQuery(int a, int b)
    {
        return depth[a] + depth[b] - 2*depth[lca(a, b)];
    }

    void dfs(int node = 1, int parent = 0, int d = 0)
    {
        ancestors[node][0] = parent;
        depth[node] = d;

        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent) dfs(neighbor, node, d + 1);
        }
    }

    void init()
    {
        dfs();
        for (int jump = 1; jump <= maxJumps; jump++)
        {
            for (int i = 1; i <= N; i++)
            {
                ancestors[i][jump] = ancestors[ancestors[i][jump - 1]][jump - 1];
            }
        }
    }

    void solve()
    {
        scanf("%d%d", &N, &Q);

        for (int i = 2; i <= N; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);

            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }

        init();

        for (int i = 1; i <= Q; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            printf("%d\n", processQuery(a, b));
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
        //solve2::solve();
    }

    return 0;
}