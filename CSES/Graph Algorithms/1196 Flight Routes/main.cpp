#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    const int maxK = 10;
    vector<pair<int, int>> neighbors[maxN + 1];
    
    int N, M, K;

    long long INF = 0x3f3f3f3f3f3f3f3f;
    
    struct NodeInfo
    {
        long long distance[maxK];

        NodeInfo()
        {
            memset(distance, INF, sizeof(distance));
        }

        int findFirstBigger(long long val)
        {
            int res = upper_bound(distance, distance + K, val) - distance;

            return res;
        }

        bool insert(long long d, int idx)
        {
            if (idx >= K)
            {
                return false;
            }

            for(; idx < K; idx++)
            {
                long long curD = distance[idx];
                distance[idx] = d;
                d = curD;
            }

            return true;
        }

        bool insert(long long d)
        {
            return insert(d, findFirstBigger(d));
        }

        bool canInsert(long long d)
        {
            return findFirstBigger(d) < K;
        }
    };

    NodeInfo info[maxN + 1];

    void solve()
    {
        scanf("%d%d%d", &N, &M, &K);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            neighbors[a].emplace_back(b, c);
        }

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;

        q.push({0, 1});
        
        while (!q.empty())
        {
            auto [distance, node] = q.top(); q.pop();

            if (!info[node].insert(distance))
            {
                continue;
            }

            for (auto& [neighbor, weight] : neighbors[node])
            {
                if (info[neighbor].canInsert(distance + weight))
                {
                    q.push({distance + weight, neighbor});
                }
            }
        }
        
        for (int i = 0; i < K; i++)
        {
            printf("%lld ", info[N].distance[i]);
        }
    }

}

namespace solve2
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    const int maxK = 10;
    vector<pair<int, int>> neighbors[maxN + 1];
    int count[maxN + 1];
    
    int N, M, K;

    long long INF = 0x3f3f3f3f3f3f3f3f;

    void solve()
    {
        scanf("%d%d%d", &N, &M, &K);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            neighbors[a].emplace_back(b, c);
        }

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;

        q.push({0, 1});
        while (!q.empty())
        {
            auto [distance, node] = q.top(); q.pop();

            if (count[node] >= K)
            {
                continue;
            }

            count[node]++;

            if (node == N)
            {
                printf("%lld ", distance);

                if (count[node] == K)
                {
                    return;
                }
            }

            for (auto& [neighbor, weight] : neighbors[node])
            {
                if (count[neighbor] < K)
                {
                    q.push({distance + weight, neighbor});
                }
            }
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