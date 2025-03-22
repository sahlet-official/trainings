#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    //bool visited[maxN + 1];
    vector<int> neighbors[maxN + 1];

    long long INF = 0x3f3f3f3f3f3f3f3f;
    long long MININF = 0xc0c0c0c0c0c0c0c0;
    
    struct NodeInfo
    {
        int from = -1;
        long long distance = MININF;
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

        info[1].distance = 0;

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
                if (info[node].distance != MININF && info[node].distance + 1 > info[neighbor].distance)
                {
                    info[neighbor].distance = info[node].distance + 1;
                    info[neighbor].from = node;
                }

                info[neighbor].in--;

                if (info[neighbor].in == 0)
                {
                    q.push(neighbor);
                }
            }
        }

        if (info[N].distance == MININF)
        {
            printf("IMPOSSIBLE");
            return;
        }
        
        deque<int> res;

        res.push_front(N);

        int node = N;
        
        while (info[node].from != -1)
        {
            node = info[node].from;
            res.push_front(node);
        }

        printf("%d\n", (int)res.size());
        
        for (int i = 0; i < res.size(); i++)
        {
            printf("%d ", res[i]);
        }
    }

}

namespace solve2
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    char visited[maxN + 1];
    vector<int> neighbors[maxN + 1];

    long long INF = 0x3f3f3f3f3f3f3f3f;
    long long MININF = 0xc0c0c0c0c0c0c0c0;
    
    struct NodeInfo
    {
        int from = -1;
        long long distance = MININF;
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
        
        info[1].distance = 0;

        for (int node : topologicalOrder)
        {
            for (int neighbor : neighbors[node])
            {
                if (info[neighbor].distance < info[node].distance + 1)
                {
                    info[neighbor].distance = info[node].distance + 1;
                    info[neighbor].from = node;
                }
            }
        }

        if (info[N].distance == MININF)
        {
            printf("IMPOSSIBLE");
            return;
        }
        
        deque<int> res;

        res.push_front(N);

        int node = N;
        
        while (info[node].from != -1)
        {
            node = info[node].from;
            res.push_front(node);
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
        //solve1::solve();
        solve2::solve();
    }

    return 0;
}