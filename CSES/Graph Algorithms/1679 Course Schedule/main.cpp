#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1 // topological order of oriented graph, DFS
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    char vis[maxN + 1];
    vector<int> neighbors[maxN + 1];
    int N, M;
    int order[maxN + 1];
    int res[maxN + 1];
    int lastFreePlace;
    bool impossible = false;

    int unvisited = 1;
    int getFirstUnvisited()
    {
        while (unvisited <= N && order[unvisited] != 0)
        {
            unvisited++;
        }
        return unvisited;
    }

    void dfs(int node)
    {
        if (vis[node])
        {
            impossible = true;
            return;
        }
        
        vis[node] = true;

        for (int neighbor : neighbors[node])
        {
            if (order[neighbor] == 0)
            {
                dfs(neighbor);
                if (impossible)
                {
                    break;
                }
            }
        }

        order[node] = lastFreePlace--;
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        lastFreePlace = N;

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            neighbors[a].push_back(b);
        }

        for (int root = getFirstUnvisited(); root <= N && lastFreePlace > 0 && !impossible; root = getFirstUnvisited())
        {
            dfs(root);
        }
        
        if (impossible)
        {
            printf("IMPOSSIBLE");
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            res[order[i]] = i;
        }

        for (int i = 1; i <= N; i++)
        {
            printf("%d ", res[i]);
        }
    }
}

namespace solve2 // topological order of oriented graph, Kahn's algorithm
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    char vis[maxN + 1];
    vector<int> neighbors[maxN + 1];
    int N, M;
    int order[maxN + 1];
    int res[maxN + 1];
    int inEdgesCount[maxN + 1];
    int firstFreePlace = 1;
    bool impossible = false;

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            neighbors[a].push_back(b);
            inEdgesCount[b]++;
        }

        queue<int> q;

        for (int i = 1; i <= N; i++)
        {
            if (inEdgesCount[i] == 0)
            {
                q.push(i);
            }
        }

        while(!q.empty())
        {
            int node = q.front(); q.pop();

            order[node] = firstFreePlace;
            firstFreePlace++;

            for (int neighbor : neighbors[node])
            {
                inEdgesCount[neighbor]--;

                if (inEdgesCount[neighbor] == 0)
                {
                    q.push(neighbor);
                }
            }
        }

        impossible = firstFreePlace <= N;

        if (impossible)
        {
            printf("IMPOSSIBLE");
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            res[order[i]] = i;
        }

        for (int i = 1; i <= N; i++)
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
        //solve2::solve();
    }

    return 0;
}