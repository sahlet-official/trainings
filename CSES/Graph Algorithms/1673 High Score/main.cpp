#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1 // Bellman–Ford algorithm (SPFA)
{
    const int maxN = 2500;
    const int maxM = 5000;
    const long long bigVal = 1e9 * (long long)(maxN + 1);
    vector<pair<int, int>> neighbors[maxN + 1];
    long long INF = 0x3f3f3f3f3f3f3f3f;
    long long MININF = 0xc0c0c0c0c0c0c0c0;
    long long distance[maxN + 1];

    int N, M;

    queue<int> oneRun(queue<int> q)
    {
        queue<int> res;
        
        while (!q.empty())
        {
            int node = q.front(); q.pop();

            for (auto& [neighbor, weight] : neighbors[node])
            {
                if (distance[node] + weight > distance[neighbor])
                {
                    distance[neighbor] = distance[node] + weight;
                    res.push(neighbor);
                }
            }
        }

        return res;
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            neighbors[a].emplace_back(b, c);
        }

        memset(distance, 0xc0, sizeof(distance));

        queue<int> q;
        q.emplace(1);
        distance[1] = 0;

        for (int i = 1; i < N && !q.empty(); i++)
        {
            q = oneRun(std::move(q));
        }

        long long res = distance[N];

        for (int i = 1; i <= 2*N && !q.empty(); i++)
        {
            q = oneRun(std::move(q));
        }

        for (int i = 1; i <= q.size(); i++)
        {
            distance[q.front()] = bigVal;
            q.push(q.front());
            q.pop();
        }

        for (int i = 1; i <= N && !q.empty(); i++)
        {
            q = oneRun(std::move(q));
        }
        
        printf("%lld", distance[N] == res ? res : -1ll);
    }

}

namespace solve2 // Bellman–Ford algorithm (SPFA)
{
    const int maxN = 2500;
    const int maxM = 5000;
    vector<pair<int, int>> neighbors[maxN + 1];
    long long INF = 0x3f3f3f3f3f3f3f3f;
    long long MININF = 0xc0c0c0c0c0c0c0c0;
    long long distance[maxN + 1];

    int N, M;

    queue<int> oneRun(queue<int> q)
    {
        queue<int> res;
        
        while (!q.empty())
        {
            int node = q.front(); q.pop();

            for (auto& [neighbor, weight] : neighbors[node])
            {
                if (distance[node] + weight > distance[neighbor])
                {
                    distance[neighbor] = distance[node] + weight;
                    res.push(neighbor);
                }
            }
        }

        return res;
    }

    bool visited[maxN + 1];

    bool dfsCanFindDestinationFrom(int node)
    {
        if (visited[node])
        {
            return false;
        }

        visited[node] = true;

        if (node == N)
        {
            return true;
        }

        for (auto& [neighbor, w] : neighbors[node])
        {
            if (dfsCanFindDestinationFrom(neighbor))
            {
                return true;
            }
        }

        return false;
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            neighbors[a].emplace_back(b, c);
        }

        memset(distance, 0xc0, sizeof(distance));

        queue<int> q;
        q.emplace(1);
        distance[1] = 0;

        for (int i = 1; i <= N && !q.empty(); i++)
        {
            q = oneRun(std::move(q));
        }

        long long res = distance[N];

        bool infRes = false;

        while (!q.empty() && !infRes)
        {
            infRes = dfsCanFindDestinationFrom(q.front());
            q.pop();
        }
        
        printf("%lld", !infRes ? res : -1ll);
    }

}

namespace solve3
{
    const int maxN = 2500;
    const int maxM = 5000;
    vector<pair<int, int>> neighbors[maxN + 1];
    vector<int> neighborsBack[maxN + 1];
    long long INF = 0x3f3f3f3f3f3f3f3f;
    long long MININF = 0xc0c0c0c0c0c0c0c0;
    long long distance[maxN + 1];

    //bool visitedStraight[maxN + 1];
    bool visitedBack[maxN + 1];

    int N, M;

    queue<int> oneRun(queue<int> q)
    {
        queue<int> res;
        
        while (!q.empty())
        {
            int node = q.front(); q.pop();

            for (auto& [neighbor, weight] : neighbors[node])
            {
                if (distance[node] + weight > distance[neighbor])
                {
                    distance[neighbor] = distance[node] + weight;
                    res.push(neighbor);
                }
            }
        }

        return res;
    }

    void dfsBack(int node)
    {
        visitedBack[node] = true;

        for (auto& neighbor : neighborsBack[node])
        {
            if (!visitedBack[neighbor])
            {
                dfsBack(neighbor);
            }
        }
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            neighbors[a].emplace_back(b, c);
            neighborsBack[b].emplace_back(a);
        }

        memset(distance, 0xc0, sizeof(distance));

        queue<int> q;
        q.emplace(1);
        distance[1] = 0;

        for (int i = 1; i <= N && !q.empty(); i++)
        {
            q = oneRun(std::move(q));
        }

        long long res = distance[N];

        bool infRes = false;

        if (!q.empty())
        {
            dfsBack(N);
        }

        while (!q.empty() && !infRes)
        {
            infRes = visitedBack[q.front()];
            q.pop();
        }
        
        printf("%lld", !infRes ? res : -1ll);
    }
}

namespace solve4 // Bellman–Ford algorithm
{
    const int maxN = 2500;
    const int maxM = 5000;
    vector<int> neighbors[maxN + 1];
    vector<int> neighborsBack[maxN + 1];
    array<int, 3> edges[maxM + 1];
    long long distance[maxN + 1];

    bool visitedStraight[maxN + 1];
    bool visitedBack[maxN + 1];

    int N, M;

    void dfsStraight(int node)
    {
        visitedStraight[node] = true;

        for (auto& neighbor : neighbors[node])
        {
            if (!visitedStraight[neighbor])
            {
                dfsStraight(neighbor);
            }
        }
    }

    void dfsBack(int node)
    {
        visitedBack[node] = true;

        for (auto& neighbor : neighborsBack[node])
        {
            if (!visitedBack[neighbor])
            {
                dfsBack(neighbor);
            }
        }
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            edges[i] = {a, b, c};
            neighbors[a].emplace_back(b);
            neighborsBack[b].emplace_back(a);
        }

        dfsStraight(1);
        dfsBack(N);

        memset(distance, 0xc0, sizeof(distance));
        distance[1] = 0;

        bool improvement = true;
        for (int i = 1; i <= N && improvement; i++)
        {
            improvement = false;
            for (int edgeIdx = 1; edgeIdx <= M; edgeIdx++)
            {
                auto [a, b, w] = edges[edgeIdx];

                if (distance[a] + w > distance[b])
                {
                    improvement = true;
                    distance[b] = distance[a] + w;

                    if (i == N)
                    {
                        if (visitedStraight[a] && visitedBack[a])
                        {
                            printf("-1");
                            return;
                        }
                    }
                }
            }
        }

        long long res = distance[N];
        
        printf("%lld", res);
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
        //solve3::solve();
        solve4::solve();
    }

    return 0;
}