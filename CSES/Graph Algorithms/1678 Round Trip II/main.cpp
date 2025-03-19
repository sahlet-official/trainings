#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    char vis[maxN + 1];
    vector<int> neighbors[maxN + 1];
    int N, M;
    deque<int> res;

    int unvisited = 1;
    int getFirstUnvisited()
    {
        while (unvisited <= N && vis[unvisited] != 0)
        {
            unvisited++;
        }
        return unvisited;
    }

    bool dfs(int node)
    {
        vis[node] = 1;
        for (int neighbor : neighbors[node])
        {
            if (vis[neighbor] == 1)
            {
                res.push_front(neighbor);
                res.push_front(node);

                return true;
            }
            else if (vis[neighbor] == 0)
            {
                if (dfs(neighbor))
                {
                    if (res.front() != res.back())
                    {
                        res.push_front(node);
                    }
                    return true;
                }
            }
        }

        vis[node] = 2;

        return false;
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            neighbors[a].push_back(b);
        }

        for (int root = getFirstUnvisited(); root <= N && res.empty(); root = getFirstUnvisited())
        {
            dfs(root);
        }
        
        if (res.empty())
        {
            printf("IMPOSSIBLE");
            return;
        }

        printf("%d\n", (int)res.size());

        for (int i = 0; i < res.size(); i++)
        {
            printf("%d ", res[i]);
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