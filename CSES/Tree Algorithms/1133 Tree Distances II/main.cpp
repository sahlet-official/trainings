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
        int subtreeSize = 0;
        long long res = 0;
    };

    NodeInfo info[maxN + 1];

    void dfs(int node = 1, int parent = 0, int depth = 0)
    {
        info[node].subtreeSize = 1;
        info[1].res += depth;
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent)
            {
                dfs(neighbor, node, depth + 1);
                info[node].subtreeSize += info[neighbor].subtreeSize;
            }
        }
    }

    void dfs2(int node = 1, int parent = 0)
    {
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent)
            {
                info[neighbor].res = info[node].res + N - 2*info[neighbor].subtreeSize;
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

        dfs();

        dfs2();

        for (int i = 1; i <= N; i++)
        {
            printf("%lld ", info[i].res);
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