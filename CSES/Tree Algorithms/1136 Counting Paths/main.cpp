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
    int ress[maxN + 1];
    int LCAs[maxN + 1];
    int ends[maxN + 1];
    int N, Q;

    int lca(int a, int b)
    {
        if (depth[a] < depth[b])
        {
            swap(a, b);
        }

        int steps = depth[a] - depth[b];

        for (int jump = maxJumps; jump >= 0; jump--)
        {
            if (steps & (1 << jump))
            {
                a = ancestors[a][jump];
            }
        }

        if (a == b)
        {
            return a;
        }

        for (int jump = maxJumps; jump >= 0; jump--)
        {
            if (ancestors[a][jump] != ancestors[b][jump])
            {
                a = ancestors[a][jump];
                b = ancestors[b][jump];
            }
        }
        
        return ancestors[a][0];
    }

    void dfs1(int node = 1, int parent = 0, int d = 0)
    {
        ancestors[node][0] = parent;
        depth[node] = d;

        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent) dfs1(neighbor, node, d + 1);
        }
    }

    int dfs2(int node = 1, int parent = 0)
    {
        int res = 0;
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent) {
                res += dfs2(neighbor, node);
            }
        }

        res += ends[node] - LCAs[node];

        ress[node] = res;

        return res - LCAs[node];
    }

    void init()
    {
        dfs1();
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
            ends[a] += 1;
            ends[b] += 1;
            LCAs[lca(a, b)] += 1;
        }

        dfs2();

        for (int i = 1; i <= N; i++)
        {
            printf("%d ", ress[i]);
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