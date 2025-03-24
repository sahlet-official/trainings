#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 2e5;
    vector<int> neighbors[maxN + 1];
    int busy[maxN + 1];
    int res;
    int N;

    struct NodeInfo
    {
        int maxDist1 = 0;
        int maxDist2 = 0;
    };

    NodeInfo info[maxN + 1];

    void dfs(int node = 1, int parent = 0)
    {
        for (int neighbor : neighbors[node])
        {
            if (neighbor != parent)
            {
                dfs(neighbor, node);

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

        res = max(res, info[node].maxDist1 + info[node].maxDist2);
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

        dfs(1);

        printf("%d ", res);
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