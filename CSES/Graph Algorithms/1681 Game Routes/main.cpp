#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

namespace solve1 // topological order of oriented graph, DFS
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    char visited[maxN + 1];
    vector<int> neighbors[maxN + 1];
    
    struct NodeInfo
    {
        int from = -1;
        long long ingressPaths = 0;
    };

    NodeInfo info[maxN + 1];

    deque<int> topologicalOrder;

    bool thereICycle = false;

    void dfs(int node)
    {
        if (visited[node] == 2)
        {
            return;
        }

        if (visited[node] == 1)
        {
            thereICycle = true;
            return;
        }

        visited[node] = 1;

        for (int neighbor : neighbors[node])
        {
            dfs(neighbor);
        }

        topologicalOrder.push_front(node);
        visited[node] = 2;
    }

    int N, M;

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            neighbors[a].emplace_back(b);
        }

        dfs(1);
        
        info[1].ingressPaths = 1;

        for (int node : topologicalOrder)
        {
            for (int neighbor : neighbors[node])
            {
                info[neighbor].ingressPaths = modSum(info[neighbor].ingressPaths, info[node].ingressPaths);
            }
        }

        printf("%d\n", (int)info[N].ingressPaths);
    }
}


namespace solve2 // topological order of oriented graph, Kahn's algorithm
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    vector<int> neighbors[maxN + 1];

    long long ZERO = 0;
    
    struct NodeInfo
    {
        int from = -1;
        long long ingressPaths = ZERO;
        int in = 0;
    };

    NodeInfo info[maxN + 1];

    int N, M;

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0;
            scanf("%d%d", &a, &b);
            neighbors[a].emplace_back(b);
            info[b].in++;
        }

        queue<int> q;

        info[1].ingressPaths = 1;

        for (int i = 1; i <= N; i++)
        {
            if (info[i].in == 0)
            {
                q.push(i);
            }
        }
        
        while (!q.empty())
        {
            int node = q.front(); q.pop();

            for (auto& neighbor : neighbors[node])
            {
                info[neighbor].ingressPaths = modSum(info[neighbor].ingressPaths, info[node].ingressPaths);

                info[neighbor].in--;

                if (info[neighbor].in == 0)
                {
                    q.push(neighbor);
                }
            }
        }

        printf("%d\n", (int)info[N].ingressPaths);
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