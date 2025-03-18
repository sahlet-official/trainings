#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1 // Dijkstra’s algorithm
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    vector<pair<int, int>> neighbors[maxN + 1];
    vector<pair<int, int>> reverseNeighbors[maxN + 1];
    array<int, 3> edges[maxM + 1];
 
    long long INF = 0x3fffffffffffffff;
    
    struct NodeInfo
    {
        long long distanceFrom1 = INF;
        long long distanceFromN = INF;
        bool visitedFrom1 = false;
        bool visitedFromN = false;
    };
 
    NodeInfo info[maxN + 1];
 
    int N, M;
 
    void solve()
    {
        scanf("%d%d", &N, &M);
 
        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            neighbors[a].emplace_back(b, c);
            reverseNeighbors[b].emplace_back(a, c);
            edges[i] = {c, a, b};
        }
 
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
 
        info[1].distanceFrom1 = 0;
        q.push({0, 1});
        
        while (!q.empty())
        {
            int node = q.top().second; q.pop();
 
            if (info[node].visitedFrom1)
            {
                continue;
            }
 
            info[node].visitedFrom1 = true;
 
            for (auto& [neighbor, weight] : neighbors[node])
            {
                auto newDistance = info[node].distanceFrom1 + weight;
 
                if (newDistance < info[neighbor].distanceFrom1)
                {
                    info[neighbor].distanceFrom1 = newDistance;
                    q.push({info[neighbor].distanceFrom1, neighbor});
                }
            }
        }
 
        info[N].distanceFromN = 0;
        q.push({0, N});
        
        while (!q.empty())
        {
            int node = q.top().second; q.pop();
 
            if (info[node].visitedFromN)
            {
                continue;
            }
 
            info[node].visitedFromN = true;
 
            for (auto& [neighbor, weight] : reverseNeighbors[node])
            {
                auto newDistance = info[node].distanceFromN + weight;
 
                if (newDistance < info[neighbor].distanceFromN)
                {
                    info[neighbor].distanceFromN = newDistance;
                    q.push({info[neighbor].distanceFromN, neighbor});
                }
            }
        }
 
        long long bestPrice = info[N].distanceFrom1;
 
        for (int i = 1; i <= M; i++)
        {
            auto [w, a, b] = edges[i];

            long long cost = w / 2 + info[a].distanceFrom1 + info[b].distanceFromN;
            bestPrice = min(bestPrice, cost);
        }
        
        
        printf("%lld ", bestPrice);
    }
 
}

namespace solve2
{
    const int maxN = 1e5;
    const int maxM = 2e5;
    vector<pair<int, int>> neighbors[maxN + 1];

    long long INF = 0x3f3f3f3f3f3f3f3f;
    
    struct NodeInfo
    {
        long long distanceWithCoupon = INF;
        long long distanceWithoutCoupon = INF;
        
        bool visitedWithCoupon = false;
        bool visitedWithoutCoupon = false;
    };

    NodeInfo info[maxN + 1];

    int N, M;

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= M; i++)
        {
            int a = 0, b = 0, c = 0;
            scanf("%d%d%d", &a, &b, &c);
            neighbors[a].emplace_back(b, c);
        }

        priority_queue<tuple<long long, int, bool>, vector<tuple<long long, int, bool>>, greater<tuple<long long, int, bool>>> q;

        info[1].distanceWithCoupon = 0;
        info[1].distanceWithoutCoupon = 0;
        q.push({0, 1, 1});
        
        while (!q.empty())
        {
            long long distance = 0;
            int node = 0;
            bool thereIsStileCoupon = 0;
            tie(distance, node, thereIsStileCoupon) = q.top();
            q.pop();

            if (info[node].visitedWithCoupon)
            {
                assert(info[node].distanceWithCoupon <= distance);
                continue;
            }

            if (!thereIsStileCoupon && info[node].visitedWithoutCoupon)
            {
                assert(info[node].distanceWithoutCoupon <= distance);
                continue;
            }

            if (thereIsStileCoupon)
            {
                info[node].visitedWithCoupon = true;
            }
            else
            {
                info[node].visitedWithoutCoupon = true;
            }

            for (auto& [neighbor, weight] : neighbors[node])
            {
                if (thereIsStileCoupon)
                {
                    auto newDistance = distance + weight;

                    if (newDistance < info[neighbor].distanceWithCoupon)
                    {
                        info[neighbor].distanceWithCoupon = newDistance;
                        q.push({newDistance, neighbor, true});
                    }

                    newDistance = distance + weight / 2;

                    if (newDistance < info[neighbor].distanceWithoutCoupon)
                    {
                        info[neighbor].distanceWithoutCoupon = newDistance;
                        q.push({newDistance, neighbor, false});
                    }
                }
                else
                {
                    auto newDistance = distance + weight;

                    if (newDistance < info[neighbor].distanceWithoutCoupon)
                    {
                        info[neighbor].distanceWithoutCoupon = newDistance;
                        q.push({newDistance, neighbor, thereIsStileCoupon});
                    }
                }
            }
        }

        long long bestPrice = info[N].distanceWithoutCoupon;

        printf("%lld ", bestPrice);
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